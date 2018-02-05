#include "Meeting.hpp"

  /**
  *   @brief constructor with argument
  */
  Meeting::Meeting(const std::string &t_sponsor,
          const std::vector<std::string> &t_participator,
          const Date &t_startTime, const Date &t_endTime,
          const std::string &t_title){
  	m_sponsor=t_sponsor;
  	m_participators=t_participator;
  	m_startDate=t_startTime;
  	m_endDate=t_endTime;
  	m_title=t_title;
  }

  /**
  * @brief copy constructor of left value
  */
  Meeting::Meeting(const Meeting &t_meeting){
  	m_sponsor=t_meeting.getSponsor();
  	m_participators=t_meeting.getParticipator();
  	m_startDate=t_meeting.getStartDate();
  	m_endDate=t_meeting.getEndDate();
  	m_title=t_meeting.getTitle();
  }

  /**
  *   @brief get the meeting's sponsor
  *   @return a string indicate sponsor
  */
  std::string Meeting::getSponsor(void) const{
  	return m_sponsor;
  }

  /**
  * @brief set the sponsor of a meeting
  * @param  the new sponsor string
  */
  void Meeting::setSponsor(const std::string &t_sponsor){
  	m_sponsor=t_sponsor;
  }

  /**
  * @brief  get the participators of a meeting
  * @return return a string vector indicate participators
  */
  std::vector<std::string> Meeting::getParticipator(void) const{
  	return m_participators;
  }

  /**
  *   @brief set the new participators of a meeting
  *   @param the new participators vector
  */
  void Meeting::setParticipator(const std::vector<std::string> &t_participators){
  	m_participators=t_participators;
  }

  /**
  * @brief add a new participator to the meeting
  * @param the new participator
  */
  void Meeting::addParticipator(const std::string &t_participator){
  	int len=m_participators.size();
  	for(int i=0;i<len;i++){
  		if(m_participators[i]==t_participator) return;
  	}
  	m_participators.push_back(t_participator);
  }

  /**
  * @brief remove a participator of the meeting
  * @param the participator to be removed
  */
  void Meeting::removeParticipator(const std::string &t_participator){
  	int len=m_participators.size();
  	for(int i=0;i<len;i++){
  		if(m_participators[i]==t_participator){
  			m_participators.erase(m_participators.begin()+i);
  			len--;
  			i--;
  		}
  	}
  }

  /**
  * @brief get the startDate of a meeting
  * @return return a string indicate startDate
  */
  Date Meeting::getStartDate(void) const{
  	return m_startDate;
  }

  /**
  * @brief  set the startDate of a meeting
  * @param  the new startdate of a meeting
  */
  void Meeting::setStartDate(const Date &t_startTime){
  	m_startDate=t_startTime;
  }

  /**
  * @brief get the endDate of a meeting
  * @return a date indicate the endDate
  */
  Date Meeting::getEndDate(void) const{
  	return m_endDate;
  }

  /**
  * @brief  set the endDate of a meeting
  * @param  the new enddate of a meeting
  */
  void Meeting::setEndDate(const Date &t_endTime){
  	m_endDate=t_endTime;
  }

  /**
  * @brief get the title of a meeting
  * @return a date title the endDate
  */
  std::string Meeting::getTitle(void) const{
  	return m_title;
  }

  /**
  * @brief  set the title of a meeting
  * @param  the new title of a meeting
  */
  void Meeting::setTitle(const std::string &t_title){
  	m_title=t_title;
  }

  /**
  * @brief check if the user take part in this meeting
  * @param t_username the source username
  * @return if the user take part in this meeting
  */
  bool Meeting::isParticipator(const std::string &t_username) const{
  	int len=m_participators.size();
  	for(int i=0;i<len;i++){
  		if(m_participators[i]==t_username) return true;
  	}
  	return false;
  }