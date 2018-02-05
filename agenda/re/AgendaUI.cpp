#include "AgendaUI.hpp"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <csignal>
#include "Exception.hpp"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::list;
using std::vector;
using std::setw;
using std::left;
using std::stringstream;

const int MAXN=200;
extern int keepRunning;
//assist function

string getString(){
	char taim[MAXN];
	memset(taim,0,sizeof(taim));
	cin.getline(taim,MAXN);
	if (!keepRunning)
		return "";
	string aim=taim;
	if (aim == "-1")
		throw CancelException();
	if(aim.size()>MAXN){
		cout<<"The input is too long!\n";
		return "";
	}
	if(aim.size()==0){
		if (keepRunning)
			cout<<"----------------\n";
		return "";
	}
	return aim;
}
int getNumber(){
	char taim[MAXN];
	memset(taim,0,sizeof(taim));
	cin.getline(taim,MAXN);
	string aim=taim;
	if (aim == "-1")
		throw CancelException();
	int len=aim.size();
	if(len>9){
		cout<<"The input is too long!\n";
		return -1;
	}
	for(auto it:aim){
		if(!isdigit(it)){
			cout<<"Input must be positive integer!\n";
			return -1;
		}
	}
	int res=atoi(taim);
	return res;
}

//public:
AgendaUI::AgendaUI(){
	startAgenda();
}
void AgendaUI::OperationLoop(void){
	string operation;
	do {
		if (!keepRunning)
			return;
		cout << "------------------------------------Agenda------------------------------------\n";
		cout << "Action:\n";
		cout << "l       -log in Agenda by username and password\n";
		cout << "r       -register an Agenda account\n";
		cout << "q       -quit Agenda\n";
		cout << "Tips:\n";
		cout << "You can back to catelog by pressing \"-1\"anytime.\n";
		cout << "You can use Ctrl + C to terminate without worring the data anytime.\n";
		cout << "------------------------------------------------------------------------------\n";
		cout << endl;
		cout << "Agenda :~$";
		try{
			operation = getString();
		}
		catch (CancelException) {
			
		}
		if (!keepRunning)
			return;
		if(operation=="l"){
			userLogIn();
		}
		else if(operation=="r"){
			userRegister();
		}
		else if(operation=="q");
		else{
			if (keepRunning)
				cout<<"No such kind of operation!\n";
		}
	}while(operation!="q");
}

//private:
/**
* constructor
*/
void AgendaUI::startAgenda(void){
	m_agendaService.startAgenda();
}

/**
* catch user's operation
* @return the operation
*/
std::string AgendaUI::getOperation(){
	cout<<"------------------------------------Agenda------------------------------------\n";
	cout<<"Action:\n";
	cout<<"o       -log out Agenda\n";
	cout<<"dc      -delete Agenda account\n";
	cout<<"lu      -list all Agenda users\n";
	cout<<"cm      -creat a meeting\n";
	cout<<"amp     -add meeting participator\n";
	cout<<"rmp     -remove meeting participator\n";
	cout<<"rqm     -request to quit meeting\n";
	cout<<"la      -list all meetings\n";
	cout<<"las     -list all sponser meetings\n";
	cout<<"lap     -list all participator meetings\n";
	cout<<"qm      -query meeting by title\n";
	cout<<"qt      -query meeting by time interval\n";
	cout<<"dm      -delete meeting by title\n";
	cout<<"da      -delete all meetings\n";
	cout << "Tips:\n";
	cout << "You can back to catelog by pressing \"-1\"anytime.\n";
	cout << "You can use Ctrl + C to terminate without worring the data anytime.\n";
	cout<<"------------------------------------------------------------------------------\n";
	cout<<endl;
	cout<<"Agenda@"<<m_userName<<" :~#";
	string res;
	try {
		res = getString();
	}
	catch (CancelException) {

	}
	return res;
}

/**
* execute the operation
* @return if the operationloop continue
*/
bool AgendaUI::executeOperation(const std::string &operation){
	if(operation=="o"){
		return false;
	}
	if(operation=="dc"){
		deleteUser();
		return false;
	}
	if(operation=="lu"){
		listAllUsers();
		return true;
	}
	if(operation=="cm"){
		createMeeting();
		return true;
	}
	if(operation=="amp"){
		addMeetingParticipator();
		return true;
	}
	if(operation=="rmp"){
		removeMeetingParticipator();
		return true;
	}
	if(operation=="rqm"){
		quitMeeting();
		return true;
	}
	if(operation=="la"){
		listAllMeetings();
		return true;
	}
	if(operation=="las"){
		listAllSponsorMeetings();
		return true;
	}
	if(operation=="lap"){
		listAllParticipateMeetings();
		return true;
	}
	if(operation=="qm"){
		queryMeetingByTitle();
		return true;
	}
	if(operation=="qt"){
		queryMeetingByTimeInterval();
		return true;
	}
	if(operation=="dm"){
		deleteMeetingByTitle();
		return true;
	}
	if(operation=="da"){
		deleteAllMeetings();
		return true;
	}
	if(keepRunning)
		cout<<"No such kind of operation!\n";
	return true;
}

/**
* user Login
*/
void AgendaUI::userLogIn(void){
	again:
	cout<<"[log in] [user name] [password]\n";
	cout<<"[log in] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	stringstream in(tin);
	if(tin=="") goto again;
	string _userName,_password;
	in>>_userName>>_password;
	if(m_agendaService.userLogIn(_userName,_password)){
		cout<<"[log in] succeed!\n";
		m_userName=_userName;
		m_userPassword=_password;
		while (keepRunning && executeOperation(getOperation())) {
			if (!keepRunning)
				return;
		}
	}
	else
		cout<<"[log in] Password error or user doesn't exist!\n";
}

/**
* user regist
*/
void AgendaUI::userRegister(void){
	again:
	cout<<"[register] [user name] [password] [email] [phone]\n";
	cout<<"[register] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	if(tin=="") goto again;
	stringstream in(tin);
	string _userName,_password,_email,_phone;
	in>>_userName>>_password>>_email>>_phone;
	bool isOk;
	cout << "[register] ";
	try {
		isOk = m_agendaService.userRegister(_userName, _password, _email, _phone);
	}
	catch (InvaildEmailException e) {
		cout << e.what();
		return;
	}
	catch (InvaildPhoneException e) {
		cout << e.what();
		return;
	}
	if(isOk){
		cout<<"succeed!\n";
		m_userName=_userName;
		m_userPassword=_password;
		while (keepRunning && executeOperation(getOperation())) {
			if (!keepRunning)
				return;
		}
	}
	else
		cout<<"This username has been registed!\n";
}

/**
* user logout
*/
void AgendaUI::userLogOut(void){
	m_userName="";
	m_userPassword="";
}

/**
* quit the Agenda
*/
void AgendaUI::quitAgenda(void){
	m_agendaService.quitAgenda();
}

/**
* delete a user from storage
*/
void AgendaUI::deleteUser(void){
	m_agendaService.deleteUser(m_userName,m_userPassword);
	cout<<"[delete Agenda account] succeed!\n";
}

/**
* list all users from storage
*/
void AgendaUI::listAllUsers(void){
	cout<<"[list all users]\n\n";
	cout<<left<<setw(25)<<"name";
	cout<<left<<setw(25)<<"email";
	cout<<left<<setw(25)<<"phone"<<endl;
	list<User> display=m_agendaService.listAllUsers();
	bool isempty = true;
	for(auto it:display){
		isempty = false;
		cout<<left<<setw(25)<<it.getName();
		cout<<left<<setw(25)<<it.getEmail();
		cout<<left<<setw(25)<<it.getPhone()<<endl;
	}
	if (isempty)
		cout << "No user!";
	cout<<endl;
}

/**
* user create a meeting with someone else
*/
void AgendaUI::createMeeting(void){
	again_num:
	cout<<"[create meeting] [the number of participators]\n";
	cout<<"[create meeting] ";
	int people_num;
	try {
		people_num = getNumber();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	if(people_num<=0) {
		goto again_num;
	}
	cout<<endl;
	vector <string> participator;
	string _title="", _startTime="", _endTime="";
again_participater_and_date:
	if (participator.size() == 0) {
		for (int i = 0; i < people_num; i++) {
			string temp;
		again_single_participater:
			cout << "[create meeting] [please enter the participator " << i + 1 << " ]\n";
			cout << "[create meeting] ";
			try {
				temp = getString();
			}
			catch (CancelException e) {
				cout << e.what();
				return;
			}
			if (!keepRunning)
				return;
			if (temp == "") {
				goto again_single_participater;
			}
			participator.push_back(temp);
			cout << endl;
		}
	}
again_date:
	if (_title == "") {
		cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
		cout << "[create meeting] ";
		string tin2;
		try {
			tin2 = getString();
		}
		catch (CancelException e) {
			cout << e.what();
			return;
		}
		if (!keepRunning)
			return;
		if (tin2 == "") goto again_date;
		stringstream in2(tin2);
		in2 >> _title >> _startTime >> _endTime;
	}
	cout << "[create meeting] ";
	bool isOk;
	try {
		isOk = m_agendaService.createMeeting(m_userName, _title, _startTime, _endTime, participator);
	}
	catch (InvaildTitleException e) {
		cout << e.what();
		_title = "";
		goto again_participater_and_date;
	}
	catch (InvaildParticipaterExistException e) {
		cout << e.what();
		participator.clear();
		goto again_participater_and_date;
	}
	catch (InvaildParticipaterRepeatedException e) {
		cout << e.what();
		participator.clear();
		goto again_participater_and_date;
	}
	catch (InvaildFormatDateException e) {
		cout << e.what();
		_title = "";
		goto again_participater_and_date;
	}
	catch (InvaildOccupliedDateException e) {
		cout << e.what();
		_title = "";
		goto again_participater_and_date;
	}
	if(isOk){
		cout<<"succeed!\n";
	}
	else
		cout<<"error!\n";
}

/**
* sponsor add a participator to the meeting
*/
void AgendaUI::addMeetingParticipator(void){
	again:
	cout<<"[add participator] [meeting title] [participator username]"<<endl;
	cout<<"[add participator] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	if(tin=="") goto again;
	stringstream in(tin);
	string _title,_participate;
	in>>_title>>_participate;
	cout<<"[add participator] ";
	bool isOk;
	try {
		isOk = m_agendaService.addMeetingParticipator(m_userName, _title, _participate);
	}
	catch (InvaildSelfisParticipaterException e) {
		cout << e.what();
		return;
	}
	catch (InvaildTitleException e) {
		cout << e.what();
		return;
	}
	catch (InvaildParticipaterExistException e) {
		cout << e.what();
		return;
	}
	catch (InvaildOccupliedDateException e) {
		cout << e.what();
		return;
	}
	if(isOk)
		cout<<"succeed!\n";
	else
		cout<<"error!\n";
}

/**
* sponsor add a participator to the meeting
*/
void AgendaUI::removeMeetingParticipator(void){
	again:
	cout<<"[remove participator] [meeting title] [participator username]"<<endl;
	cout<<"[remove participator] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	if(tin=="") goto again;
	stringstream in(tin);
	string _title,_participate;
	in>>_title>>_participate;
	cout<<"[remove participator] ";
	if(m_agendaService.removeMeetingParticipator(m_userName,_title,_participate))
		cout<<"succeed!\n";
	else
		cout<<"No such title of meeting or no participater exist!\n";
}

/**
* user quit from meeting
*/
void AgendaUI::quitMeeting(void){
	again:
	cout<<"[quit meeting] [meeting title]"<<endl;
	cout<<"[quit meeting] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	if(tin=="") goto again;
	stringstream in(tin);
	string _title;
	in>>_title;
	cout<<"[quit meeting] ";
	if (m_agendaService.quitMeeting(m_userName, _title))
		cout << "succeed!\n";
	else
		cout << "Havn't participated in this meeting!\n";
}

/**
* list all meetings from storage
*/
void AgendaUI::listAllMeetings(void){
	cout<<"[list all meetings]\n\n";
	cout<<left<<setw(25)<<"title";
	cout<<left<<setw(25)<<"sponser";
	cout<<left<<setw(25)<<"start time";
	cout<<left<<setw(25)<<"end time";
	cout<<left<<setw(25)<<"participators"<<endl;
	list<Meeting> display=m_agendaService.listAllMeetings(m_userName);
	printMeetings(display);
}

/**
* list all meetings that this user sponsored
*/
void AgendaUI::listAllSponsorMeetings(void){
	cout<<"[list all sponser meetings]\n\n";
	cout<<left<<setw(25)<<"title";
	cout<<left<<setw(25)<<"sponser";
	cout<<left<<setw(25)<<"start time";
	cout<<left<<setw(25)<<"end time";
	cout<<left<<setw(25)<<"participators"<<endl;
	list<Meeting> display=m_agendaService.listAllSponsorMeetings(m_userName);
	printMeetings(display);
}

/**
* list all meetings that this user take part in
*/
void AgendaUI::listAllParticipateMeetings(void){
	cout<<"[list all participator meetings]\n\n";
	cout<<left<<setw(25)<<"title";
	cout<<left<<setw(25)<<"sponser";
	cout<<left<<setw(25)<<"start time";
	cout<<left<<setw(25)<<"end time";
	cout<<left<<setw(25)<<"participators"<<endl;
	list<Meeting> display=m_agendaService.listAllParticipateMeetings(m_userName);
	printMeetings(display);
}

/**
* search meetings by title from storage
*/
void AgendaUI::queryMeetingByTitle(void){
	again:
	cout<<"[query meeting] [title]\n";
	cout<<"[query meeting] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	if(tin=="") goto again;
	stringstream in(tin);
	string _title;
	in>>_title;
	cout<<left<<setw(25)<<"title";
	cout<<left<<setw(25)<<"sponser";
	cout<<left<<setw(25)<<"start time";
	cout<<left<<setw(25)<<"end time";
	cout<<left<<setw(25)<<"participators"<<endl;
	list<Meeting> display=m_agendaService.meetingQuery(m_userName,_title);
	printMeetings(display);
}

/**
* search meetings by timeinterval from storage
*/
void AgendaUI::queryMeetingByTimeInterval(void){
	again:
	cout<<"[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
	cout<<"[query meetings] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	if(tin=="") goto again;
	stringstream in(tin);
	string _startTime,_endTime;
	in>>_startTime>>_endTime;
	list<Meeting> display;
	try {
		display = m_agendaService.meetingQuery(m_userName, _startTime, _endTime);
	}
	catch (InvaildFormatDateException e) {
		cout << e.what();
		return;
	}
	cout << left << setw(25) << "title";
	cout << left << setw(25) << "sponser";
	cout << left << setw(25) << "start time";
	cout << left << setw(25) << "end time";
	cout << left << setw(25) << "participators" << endl;
	printMeetings(display);
}

/**
* delete meetings by title from storage
*/
void AgendaUI::deleteMeetingByTitle(void){
	again:
	cout<<"[delete meeting] [title]\n";
	cout<<"[delete meeting] ";
	string tin;
	try {
		tin = getString();
	}
	catch (CancelException e) {
		cout << e.what();
		return;
	}
	if (!keepRunning)
		return;
	stringstream in(tin);
	if(tin=="") goto again;
	string _title;
	in>>_title;
	cout<<"[delete meeting] ";
	bool isOk;
	try {
		isOk = m_agendaService.deleteMeeting(m_userName, _title);
	}
	catch (InvaildFormatDateException e) {
		cout << e.what();
		return;
	}
	if(isOk)
		cout<<"succeed!\n";
	else
		cout<<"No such meeting!\n";
}

/**
* delete all meetings that this user sponsored
*/
void AgendaUI::deleteAllMeetings(void){
	cout << "[delete all meetings] ";
	if (m_agendaService.deleteAllMeetings(m_userName))
		cout << "succeed!\n";
	else
		cout << "No such meeting!\n";
}

/**
* show the meetings in the screen
*/
void AgendaUI::printMeetings(const std::list<Meeting> &t_meetings){
	bool isempty = true;
	for(auto it:t_meetings){
		isempty = false;
		cout<<left<<setw(25)<<it.getTitle();
		cout<<left<<setw(25)<<it.getSponsor();
		cout<<left<<setw(25)<<Date::dateToString(it.getStartDate());
		cout<<left<<setw(25)<<Date::dateToString(it.getEndDate());
		vector <string> p_display=it.getParticipator();
		bool sym=false;
		for(auto itp:p_display){
			if(!sym)
				sym=true;
			else
				cout<<",";
			cout<<itp;
		}
		cout<<endl;
	}
	if (isempty)
		cout << "----------------------------------------------------none----------------------------------------------------";
	cout<<endl<<endl;
}