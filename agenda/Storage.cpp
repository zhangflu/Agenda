#include "Storage.hpp"
#include "User.hpp"
#include "Date.hpp"
#include "Meeting.hpp"
#include "Path.hpp"
#include <cstring>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <vector>
const int MAXN = 500;

using std:: endl;

  std::shared_ptr<Storage> Storage::m_instance(nullptr);
//private:
  /**
  *   default constructor
  */
  Storage::Storage(){
    readFromFile();
    m_dirty=false;
  }

  void encfile(const char *in_filename,const char *pwd,const char *out_file)
  {
	  FILE *fp1, *fp2;
	  register char ch;
	  int j = 0;
	  int j0 = 0;
	  fp1 = fopen(in_filename, "r");
	  if (fp1 == NULL) {
		  printf("cannot open in-file./n");
		  exit(1);
	  }
	  fp2 = fopen(out_file, "w");
	  if (fp2 == NULL) {
		  printf("cannot open or create out-file./n");
		  exit(1);
	  }

	  while (pwd[++j0]);

	  ch = fgetc(fp1);


	  while (!feof(fp1)) {
		  if (j0 >7)
			  j0 = 0;
		  ch += pwd[j0++];
		  fputc(ch, fp2);
		  ch = fgetc(fp1);
	  }
	  fclose(fp1);
	  fclose(fp2);
  }


  void decryptfile(const char *in_filename,const char *pwd, const char *out_file)
  {
	  FILE *fp1, *fp2;
	  register char ch;
	  int j = 0;
	  int j0 = 0;
	  fp1 = fopen(in_filename, "r");
	  if (fp1 == NULL) {
		  printf("cannot open in-file./n");
		  exit(1);
	  }
	  fp2 = fopen(out_file, "w");
	  if (fp2 == NULL) {
		  printf("cannot open or create out-file./n");
		  exit(1);
	  }

	  while (pwd[++j0]);
	  ch = fgetc(fp1);

	  while (!feof(fp1)) {
		  if (j0 >7)
			  j0 = 0;
		  ch -= pwd[j0++];
		  fputc(ch, fp2);
		  ch = fgetc(fp1);
	  }
	  fclose(fp1);
	  fclose(fp2);
  }

  /**
  *   read file content into memory
  *   @return if success, true will be returned
  */
  bool Storage::readFromFile(void){
	decryptfile(Path::s_meetingPath, "123456", Path::meetingPath);
	decryptfile(Path::s_userPath, "123456", Path::userPath);
    std::ifstream fin;
    fin.open(Path::userPath);
    if(!fin) return false;
    while (fin.good()){
      std::string t_name;
      std::string t_password;
      std::string t_email;
      std::string t_phone;
      char temp_arr[MAXN];
      memset(temp_arr,0,sizeof(temp_arr));
      fin.getline(temp_arr,MAXN);
      if(strlen(temp_arr)==0) break;
      std:: string temp_string=temp_arr;
      int start_index=0;
      int end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      t_name=temp_string.substr(start_index+1,end_index-start_index-1);
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      t_password=temp_string.substr(start_index+1,end_index-start_index-1);
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      t_email=temp_string.substr(start_index+1,end_index-start_index-1);
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      t_phone=temp_string.substr(start_index+1,end_index-start_index-1);
      m_userList.push_back(User(t_name,t_password,t_email,t_phone));
    }
    fin.close();
    fin.open(Path::meetingPath);
    if(!fin) return false;
    while (fin.good()){
      std::string m_sponsor;
      std::vector<std::string> m_participators;
      Date m_startDate;
      Date m_endDate;
      std::string m_title;
      char temp_arr[MAXN];
      memset(temp_arr,0,sizeof(temp_arr));
      fin.getline(temp_arr,MAXN);
      if(strlen(temp_arr)==0) break;
      std:: string temp_string=temp_arr;
      //sponsor
      int start_index=0;
      int end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      m_sponsor=temp_string.substr(start_index+1,end_index-start_index-1);
      //partcipate
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      std::string t_participators;
      t_participators=temp_string.substr(start_index+1,end_index-start_index-1);
      int p_start_index=0;
      int p_end_index=p_start_index+1;
      int p_len=t_participators.size();
      while(p_start_index<p_len){
        while(p_end_index<p_len && t_participators[p_end_index]!='&'){
          p_end_index++;
        }
        if(p_end_index>=p_len) break;
        m_participators.push_back(t_participators.substr(p_start_index,p_end_index-p_start_index));
        p_start_index=p_end_index+1;
        p_end_index=p_start_index+1;
      }
      m_participators.push_back(t_participators.substr(p_start_index,p_end_index-p_start_index));
      //startDate
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      m_startDate=Date(temp_string.substr(start_index+1,end_index-start_index-1));
      //endDate
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      m_endDate=Date(temp_string.substr(start_index+1,end_index-start_index-1));
      //title
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      m_title=temp_string.substr(start_index+1,end_index-start_index-1);
      m_meetingList.push_back(Meeting(m_sponsor,m_participators,m_startDate,m_endDate,m_title));
    }
    fin.close();
    return true;
  }

  /**
  *   write file content from memory
  *   @return if success, true will be returned
  */
  bool Storage::writeToFile(void){
    std::ofstream fout;
    fout.open(Path::userPath);
    if(!fout) return false;
    bool flag_n=false;
    for(auto it_user: m_userList){
      if(flag_n==false) flag_n=true;
      else fout<<endl;
      fout<<"\""<<it_user.getName()<<"\",\""<<it_user.getPassword()<<"\",\""<<it_user.getEmail()<<"\",\""<<it_user.getPhone()<<"\"";
    }
    fout.close();
    fout.open(Path::meetingPath);
    if(!fout) return false;
    flag_n=false;
    for(auto it_meeting:m_meetingList){
      if(flag_n==false) flag_n=true;
      else fout<<endl;
      fout<<"\""<<it_meeting.getSponsor()<<"\",\"";
      bool flag_f=false;
      std::vector<std::string> sm_participator=it_meeting.getParticipator();
      for(auto it_part:sm_participator){
        if(flag_f==false) flag_f=true;
        else fout<<'&';
        fout<<it_part;
      }
      fout<<"\",\""<<Date::dateToString(it_meeting.getStartDate())<<"\",\""<<Date::dateToString(it_meeting.getEndDate())<<"\",\""<<it_meeting.getTitle()<<"\"";
    }
    fout.close();
    m_dirty=false;
	encfile(Path::meetingPath,"123456",Path::s_meetingPath);
	encfile(Path::userPath, "123456", Path::s_userPath);
    return true;
  }

//public:
  /**
  * get Instance of storage
  * @return the pointer of the instance
  */
  std::shared_ptr<Storage> Storage::getInstance(void){
  	if(!m_instance) m_instance=std::shared_ptr<Storage>(new Storage());
    return m_instance;
  }

  /**
  *   destructor
  */
  Storage::~Storage(){
  	if(m_dirty) writeToFile();
  }

  // CRUD for User & Meeting
  // using C++11 Function Template and Lambda Expressions

  /**
  * create a user
  * @param a user object
  */
  void Storage::createUser(const User &t_user){
    /*for(auto it_user:m_userList){
      if(it_user.getName()==t_user.getName()) return;
    }*/
    m_dirty=true;
    m_userList.push_back(t_user);
  }

  /**
  * query users
  * @param a lambda function as the filter
  * @return a list of fitted users
  */
  std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) const{
    std::list<User> res;
    for(auto it_user:m_userList){
      if(filter(it_user)) res.push_back(it_user);
    }
    return res;
  }

  /**
  * update users
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the user
  * @return the number of updated users
  */
  int Storage::updateUser(std::function<bool(const User &)> filter,
                 std::function<void(User &)> switcher){
    int count=0;
    for(auto& it_user:m_userList){
      if(filter(it_user)) {
        switcher(it_user);
        count++;
      }
    }
    if(count) m_dirty=true;
    return count;
  }

  /**
  * delete users
  * @param a lambda function as the filter
  * @return the number of deleted users
  */
  int Storage::deleteUser(std::function<bool(const User &)> filter){
    int count=0;
    std::list<User>::iterator it_user_ptr;
    for(it_user_ptr=m_userList.begin();it_user_ptr!=m_userList.end();){
      if(filter(*it_user_ptr)) {
        it_user_ptr=m_userList.erase(it_user_ptr);
        count++;
      }
      else it_user_ptr++;
    }
    if(count) m_dirty=true;
    return count;
  }

  /**
  * create a meeting
  * @param a meeting object
  */
  void Storage::createMeeting(const Meeting &t_meeting){
    m_dirty=true;
    m_meetingList.push_back(t_meeting);
  }

  /**
  * query meetings
  * @param a lambda function as the filter
  * @return a list of fitted meetings
  */
  std::list<Meeting> Storage::queryMeeting(
    std::function<bool(const Meeting &)> filter) const{
    std::list<Meeting> res;
    for(auto it_meeting:m_meetingList){
      if(filter(it_meeting)) res.push_back(it_meeting);
    }
    return res;
  }

  /**
  * update meetings
  * @param a lambda function as the filter
  * @param a lambda function as the method to update the meeting
  * @return the number of updated meetings
  */
  int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher){
    int count=0;
    for(auto& it_meeting:m_meetingList){
      if(filter(it_meeting)) {
        switcher(it_meeting);
        count++;
      }
    }
    if(count) m_dirty=true;
    return count;
  }

  /**
  * delete meetings
  * @param a lambda function as the filter
  * @return the number of deleted meetings
  */
  int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter){
    int count=0;
    std::list<Meeting>::iterator it_meeting_ptr;
    for(it_meeting_ptr=m_meetingList.begin();it_meeting_ptr!=m_meetingList.end();){
      if(filter(*it_meeting_ptr)) {
        it_meeting_ptr=m_meetingList.erase(it_meeting_ptr);
        count++;
      }
      else it_meeting_ptr++;
    }
    if(count) m_dirty=true;
    return count;
  }

  /**
  * sync with the file
  */
  bool Storage::sync(void){
  	if(!m_dirty) return true;
    if(writeToFile()) return true;
    return false;
  }