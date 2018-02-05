#include "Date.hpp"
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
const int MAXN=100;
  /**
  * @brief default constructor
  */
  Date::Date(){
  	m_year=0;
  	m_month=0;
  	m_day=0;
  	m_hour=0;
  	m_minute=0;
  }

  /**
  * @brief constructor with arguments
  */
  Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute){
  	m_year=t_year;
  	m_month=t_month;
  	m_day=t_day;
  	m_hour=t_hour;
  	m_minute=t_minute;
  }

  /**
  * @brief constructor with a string
  */
  Date::Date(const std::string &t_dateString){
    m_year=0;
    m_month=0;
    m_day=0;
    m_hour=0;
    m_minute=0;
    int len=t_dateString.size();
    if(len!=16) return;
    int check_index=0;
    if(t_dateString[4]!='-' || t_dateString[7]!='-' || t_dateString[10]!='/' || t_dateString[13]!=':') return;
    for(check_index=0;check_index<=3;check_index++){
      if(!isdigit(t_dateString[check_index])) return;
    }
    for(check_index=5;check_index<=6;check_index++){
      if(!isdigit(t_dateString[check_index])) return;
    }
    for(check_index=8;check_index<=9;check_index++){
      if(!isdigit(t_dateString[check_index])) return;
    }
    for(check_index=11;check_index<=12;check_index++){
      if(!isdigit(t_dateString[check_index])) return;
    }
    for(check_index=14;check_index<=15;check_index++){
      if(!isdigit(t_dateString[check_index])) return;
    }
  	std::stringstream ss(t_dateString);
  	char temp_char;
  	ss>>m_year>>temp_char;
  	ss>>m_month>>temp_char;
  	ss>>m_day>>temp_char;
  	ss>>m_hour>>temp_char;
  	ss>>m_minute;
  }
  /**
  * @brief return the year of a Date
  * @return   a integer indicate the year of a date
  */
  int Date::getYear(void) const{
  	return m_year;
  }

  /**
  * @brief set the year of a date
  * @param a integer indicate the new year of a date
  */
  void Date::setYear(const int t_year){
  	m_year=t_year;
  }

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
  int Date::getMonth(void) const{
  	return m_month;
  }

  /**
  * @brief set the month of a date
  * @param a integer indicate the new month of a date
  */
  void Date::setMonth(const int t_month){
  	m_month=t_month;
  }

  /**
  * @brief return the day of a Date
  * @return   a integer indicate the day of a date
  */
  int Date::getDay(void) const{
  	return m_day;
  }

  /**
  * @brief set the day of a date
  * @param a integer indicate the new day of a date
  */
  void Date::setDay(const int t_day){
  	m_day=t_day;
  }

  /**
  * @brief return the hour of a Date
  * @return   a integer indicate the hour of a date
  */
  int Date::getHour(void) const{
  	return m_hour;
  }

  /**
  * @brief set the hour of a date
  * @param a integer indicate the new hour of a date
  */
  void Date::setHour(const int t_hour){
  	m_hour=t_hour;
  }

  /**
  * @brief return the minute of a Date
  * @return   a integer indicate the minute of a date
  */
  int Date::getMinute(void) const{
  	return m_minute;
  }

  /**
  * @brief set the minute of a date
  * @param a integer indicate the new minute of a date
  */
  void Date::setMinute(const int t_minute){
  	m_minute=t_minute;
  }

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
  bool Date::isValid(const Date &t_date){
  	if(t_date.m_year<1000 || t_date.m_year>9999) return false;
  	if(t_date.m_month<1 || t_date.m_month>12) return false;
  	if(t_date.m_day<1 || t_date.m_day>31) return false;
  	if(t_date.m_hour<0 || t_date.m_hour>23) return false;
  	if(t_date.m_minute<0 || t_date.m_minute>59) return false;
    int pin_year[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int run_year[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
    bool is_run=false;
    if(t_date.getYear()%4==0 && t_date.getYear()%100!=0) is_run=true;
    else if(t_date.getYear()%400==0) is_run=true;
    if(!is_run){
      if(pin_year[t_date.getMonth()]<t_date.getDay()) return false;
    }
    else{
      if(run_year[t_date.getMonth()]<t_date.getDay()) return false;
    }
  	return true;
  }

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  Date Date::stringToDate(const std::string &t_dateString){
  	int len=t_dateString.size();
  	if(len!=16) return Date();
  	int check_index=0;
  	if(t_dateString[4]!='-' || t_dateString[7]!='-' || t_dateString[10]!='/' || t_dateString[13]!=':') return Date();
  	for(check_index=0;check_index<=3;check_index++){
  		if(!isdigit(t_dateString[check_index])) return Date();
  	}
  	for(check_index=5;check_index<=6;check_index++){
  		if(!isdigit(t_dateString[check_index])) return Date();
  	}
  	for(check_index=8;check_index<=9;check_index++){
  		if(!isdigit(t_dateString[check_index])) return Date();
  	}
  	for(check_index=11;check_index<=12;check_index++){
  		if(!isdigit(t_dateString[check_index])) return Date();
  	}
  	for(check_index=14;check_index<=15;check_index++){
  		if(!isdigit(t_dateString[check_index])) return Date();
  	}
  	return Date(t_dateString);
  }

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  std::string Date::dateToString(const Date &t_date){
    if(!isValid(t_date)) return "0000-00-00/00:00";
  	char temp_string[MAXN];
  	memset(temp_string,0,sizeof(temp_string));
  	sprintf(temp_string,"%04d-%02d-%02d/%02d:%02d",t_date.getYear(),t_date.getMonth(),t_date.getDay(),t_date.getHour(),t_date.getMinute());
  	std::string res=temp_string;
  	return res;
  }

  /**
  *  @brief overload the assign operator
  */
  Date& Date::operator=(const Date &t_date){
  	m_year=t_date.getYear();
  	m_month=t_date.getMonth();
  	m_day=t_date.getDay();
  	m_hour=t_date.getHour();
  	m_minute=t_date.getMinute();
	return *this;
  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool Date::operator==(const Date &t_date) const{
  	if(m_year!=t_date.getYear()) return false;
  	if(m_month!=t_date.getMonth()) return false;
  	if(m_day!=t_date.getDay()) return false;
  	if(m_hour!=t_date.getHour()) return false;
  	if(m_minute!=t_date.getMinute()) return false;
  	return true;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool Date::operator>(const Date &t_date) const{
  	if(m_year>t_date.getYear()) return true;
    if(m_year<t_date.getYear()) return false;
    if(m_month>t_date.getMonth()) return true;
    if(m_month<t_date.getMonth()) return false;
    if(m_day>t_date.getDay()) return true;
    if(m_day<t_date.getDay()) return false;
    if(m_hour>t_date.getHour()) return true;
    if(m_hour<t_date.getHour()) return false;
    if(m_minute>t_date.getMinute()) return true;
    return false;

  }

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool Date::operator<(const Date &t_date) const{
  	if(*this==t_date || *this>t_date) return false;
    return true;
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool Date::operator>=(const Date &t_date) const{
  	if(*this<t_date) return false;
  	return true;
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool Date::operator<=(const Date &t_date) const{
  	if(*this>t_date) return false;
  	return true;
  }