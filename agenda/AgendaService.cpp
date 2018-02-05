#include "AgendaService.hpp"
#include "Exception.hpp"
#include <regex>
//assist function
bool VerifyEmail(string e) {
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	bool valid = regex_match(e,pattern);
	return valid;
}
bool VerifyPhone(string e) {
	const regex pattern("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");
	bool valid = regex_match(e, pattern);
	return valid;
}
/**
* constructor
*/
AgendaService::AgendaService(){
	startAgenda();
}

/**
* destructor
*/
AgendaService::~AgendaService(){
	quitAgenda();
}

/**
* check if the username match password
* @param userName the username want to login
* @param password the password user enter
* @return if success, true will be returned
*/
bool AgendaService::userLogIn(const std::string &userName, const std::string &password){
	std::list<User> res=m_storage->queryUser([userName,password](const User &c){
		if(c.getName()==userName && c.getPassword()==password) return true;
		return false;
	});
	if(res.empty()) return false;
	return true;
}

/**
* regist a user
* @param userName new user's username
* @param password new user's password
* @param email new user's email
* @param phone new user's phone
* @return if success, true will be returned
*/
bool AgendaService::userRegister(const std::string &userName, const std::string &password,
                const std::string &email, const std::string &phone){
	//no repeat
	std::list<User> res=m_storage->queryUser([userName,password](const User &c){
		if(c.getName()==userName) return true;
		return false;
	});
	if(!res.empty()) return false;
	if (!VerifyEmail(email))
		throw InvaildEmailException();
	if (!VerifyPhone(phone))
		throw InvaildPhoneException();
	User adder(userName,password,email,phone);
	m_storage->createUser(adder);
	return true;
}

/**
* delete a user
* @param userName user's username
* @param password user's password
* @return if success, true will be returned
*/
bool AgendaService::deleteUser(const std::string &userName, const std::string &password){
	//delete self
	int del_num=m_storage->deleteUser([userName,password](const User &c){
		if(c.getName()==userName && c.getPassword()==password) return true;
		return false;
	});
	if(del_num==0) return false;
	//delete sponser meeting
	m_storage->deleteMeeting([userName](const Meeting &c){
		if(c.getSponsor()==userName) return true;
		return false;
	});
	//update part meeting
	m_storage->updateMeeting([userName](const Meeting &c){
		if(c.isParticipator(userName)) return true;
		return false;
	},[userName](Meeting & c){
		c.removeParticipator(userName);
	});
	//delete no participate meeting
	m_storage->deleteMeeting([](const Meeting &c){
		std::vector<std::string> res=c.getParticipator();
		if(res.empty()) return true;
		return false;
	});
	return true;
}

/**
* list all users from storage
* @return a user list result
*/
std::list<User> AgendaService::listAllUsers(void) const{
	std::list<User> res=m_storage->queryUser([](const User &c){
		return true;
	});
	return res;
}

//assist function
bool time_valid(Date o_s,Date o_e,Date n_s,Date n_e){
	if(n_s>n_e) return false;
	if(n_s<=o_s && n_e>=o_e) return false;
	if(n_s>o_s && n_s<o_e) return false;
	if(n_e>o_s && n_e<o_e) return false;
	return true;
}

/**
* create a meeting
* @param userName the sponsor's userName
* @param title the meeting's title
* @param participator the meeting's participator
* @param startData the meeting's start date
* @param endData the meeting's end date
* @return if success, true will be returned
*/
bool AgendaService::createMeeting(const std::string &userName, const std::string &title,
                 const std::string &startDate, const std::string &endDate,
                 const std::vector<std::string> &participator){
	//check date
	if(!Date::isValid(Date::stringToDate(startDate)) || !Date::isValid(Date::stringToDate(endDate))) 
		throw InvaildFormatDateException();
	if(Date::stringToDate(startDate)>=Date::stringToDate(endDate)) 
		throw InvaildFormatDateException();
	//check title
	std::list<Meeting> res=m_storage->queryMeeting([title](const Meeting &c){
		if(c.getTitle()==title) 
			return true;
		return false;
	});
	if (!res.empty())
		throw InvaildTitleException();
	//check people is exist
	std::vector<std::string> check_people=participator;
	check_people.push_back(userName);
	for(auto it:check_people){
		std::list<User> temp=m_storage->queryUser([it](const User &c){
			if(it==c.getName()) return true;
			return false;
		});
		if (temp.empty())
			throw InvaildParticipaterExistException();
	}
	int len=check_people.size();
	for(int i=0;i<len;i++){
		for(int j=i+1;j<len;j++){
			if (check_people[i] == check_people[j])
				throw InvaildParticipaterRepeatedException();
		}
	}
	//check time
	std::list<Meeting> unable_meeting=m_storage->queryMeeting([check_people,startDate,endDate](const Meeting &c){
		for(auto it:check_people){
			if(it==c.getSponsor() || c.isParticipator(it)){
				if(!time_valid(c.getStartDate(),c.getEndDate(),Date::stringToDate(startDate),Date::stringToDate(endDate))) 
					return true;
			}
		}
		return false;
	});
	if (!unable_meeting.empty())
		throw InvaildOccupliedDateException();
	//creat meeting
	Meeting adder(userName,participator,Date::stringToDate(startDate),Date::stringToDate(endDate),title);
	m_storage->createMeeting(adder);
	return true;
}

/**
* add a participator to a meeting
* @param userName the sponsor's userName
* @param title the meeting's title
* @param participator the meeting's participator
* @return if success, true will be returned
*/
bool AgendaService::addMeetingParticipator(const std::string &userName,
                          const std::string &title,
                          const std::string &participator){
	//check is self
	if (userName == participator)
		throw InvaildSelfisParticipaterException();
	//check title exist
	std::list<Meeting> res=m_storage->queryMeeting([title](const Meeting &c){
		if(c.getTitle()==title) return true;
		return false;
	});
	if (res.empty())
		throw InvaildTitleException();
	Meeting _this=*(res.begin());
	//check participator is exist
	std::list<User> temp=m_storage->queryUser([participator](const User &c){
		if(participator==c.getName()) return true;
		return false;
	});
	if (temp.empty())
		throw InvaildParticipaterExistException();
	//check time
	std::list<Meeting> unable_meeting=m_storage->queryMeeting([participator,_this](const Meeting &c){
		if(participator==c.getSponsor() || c.isParticipator(participator)){
			if(!time_valid(c.getStartDate(),c.getEndDate(),_this.getStartDate(),_this.getEndDate())) return true;
		}
		return false;
	});
	if (!unable_meeting.empty())
		throw InvaildOccupliedDateException();
	//add participator
	m_storage->updateMeeting([title](const Meeting &c){
		if(c.getTitle()==title) return true;
		return false;
	},[participator](Meeting &c){
		c.addParticipator(participator);
	});
	return true;
}

/**
* remove a participator from a meeting
* @param userName the sponsor's userName
* @param title the meeting's title
* @param participator the meeting's participator
* @return if success, true will be returned
*/
bool AgendaService::removeMeetingParticipator(const std::string &userName,
                             const std::string &title,
                             const std::string &participator){
	int ok_num=m_storage->updateMeeting([userName,title,participator](const Meeting &c){
		if(c.getSponsor()==userName && c.getTitle()==title && c.isParticipator(participator))
			return true;
		return false;
	},[participator](Meeting &c){
		c.removeParticipator(participator);
	});
	m_storage->deleteMeeting([](const Meeting &c){
		std::vector<std::string> res=c.getParticipator();
		if(res.empty()) return true;
		return false;
	});
	if(ok_num) return true;
	return false;
}

/**
* quit from a meeting
* @param userName the current userName. no need to be the sponsor
* @param title the meeting's title
* @return if success, true will be returned
*/
bool AgendaService::quitMeeting(const std::string &userName, const std::string &title){
	int ok_num=m_storage->updateMeeting([userName,title](const Meeting &c){
		if(c.getTitle()==title && c.isParticipator(userName))
			return true;
		return false;
	},[userName](Meeting &c){
		c.removeParticipator(userName);
	});
	//remove no participate
	m_storage->deleteMeeting([](const Meeting &c){
		std::vector<std::string> res=c.getParticipator();
		if(res.empty()) return true;
		return false;
	});	
	if(ok_num) return true;
	return false;
}

/**
* search a meeting by username and title
* @param uesrName the sponsor's userName
* @param title the meeting's title
* @return a meeting list result
*/
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                              const std::string &title) const{
	std::list<Meeting> res;
	res=m_storage->queryMeeting([userName,title](const Meeting &c){
		if((c.getSponsor()==userName || c.isParticipator(userName))&& c.getTitle()==title) return true;
		return false;
	});
	return res;
}
/**
* search a meeting by username, time interval
* @param uesrName the sponsor's userName
* @param startDate time interval's start date
* @param endDate time interval's end date
* @return a meeting list result
*/
std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                              const std::string &startDate,
                              const std::string &endDate) const{
	std::list<Meeting> res;
	//check date
	Date start(startDate);
	Date end(endDate);
	if (!Date::isValid(start) || !Date::isValid(end) || start>end)
		throw InvaildFormatDateException();
	res=m_storage->queryMeeting([userName,start,end](const Meeting &c){
		if(c.getSponsor()==userName || c.isParticipator(userName)){
			if(c.getEndDate()>=start && c.getStartDate()<=end)
				return true;
		}
		return false;
	});
	return res;	
}

/**
* list all meetings the user take part in
* @param userName user's username
* @return a meeting list result
*/
std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const{
	std::list<Meeting> res;
	res=m_storage->queryMeeting([userName](const Meeting &c){
		if(c.isParticipator(userName) || c.getSponsor()==userName) return true;
		return false;
	});
	return res;
}

/**
* list all meetings the user sponsor
* @param userName user's username
* @return a meeting list result
*/
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const{
	std::list<Meeting> res;
	res=m_storage->queryMeeting([userName](const Meeting &c){
		if(c.getSponsor()==userName) return true;
		return false;
	});
	return res;
}

/**
* list all meetings the user take part in and sponsor by other
* @param userName user's username
* @return a meeting list result
*/
std::list<Meeting> AgendaService::listAllParticipateMeetings(
    const std::string &userName) const{
	std::list<Meeting> res;
	res=m_storage->queryMeeting([userName](const Meeting &c){
		if(c.isParticipator(userName)) return true;
		return false;
	});
	return res;
}

/**
* delete a meeting by title and its sponsor
* @param userName sponsor's username
* @param title meeting's title
* @return if success, true will be returned
*/
bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title){
	int ok_num=m_storage->deleteMeeting([userName,title](const Meeting &c){
		if(userName==c.getSponsor() && title==c.getTitle()) return true;
		return false;
	});
	if(ok_num) return true;
	return false;
}

/**
* delete all meetings by sponsor
* @param userName sponsor's username
* @return if success, true will be returned
*/
bool AgendaService::deleteAllMeetings(const std::string &userName){
	int ok_num=m_storage->deleteMeeting([userName](const Meeting &c){
		if(userName==c.getSponsor()) return true;
		return false;
	});
	if(ok_num) return true;
	return false;
}

/**
* start Agenda service and connect to storage
*/
void AgendaService::startAgenda(void){
	m_storage=Storage::getInstance();
}

/**
* quit Agenda service
*/
void AgendaService::quitAgenda(void){
	m_storage->sync();
}