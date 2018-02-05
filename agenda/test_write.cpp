#include <cstring>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
const int MAXN = 100;
int main(){
	ifstream fin;
    fin.open("users.csv");
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
      cout<<t_name<<endl<<t_password<<endl<<t_email<<endl<<t_phone<<endl;
  }
  fin.close();
    fin.open("meetings.csv");
    while (fin.good()){
      std::string m_sponsor;
      //std::vector<std::string> m_participators;
      //Date m_startDate;
      //Date m_endDate;
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
      cout<<temp_string.substr(start_index+1,end_index-start_index-1)<<endl;
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
        cout<<(t_participators.substr(p_start_index,p_end_index-p_start_index))<<endl;
        p_start_index=p_end_index+1;
        p_end_index=p_start_index+1;
      }
      cout<<(t_participators.substr(p_start_index,p_end_index-p_start_index))<<endl;
      //cout<<t_participators<<endl;
      //startDate
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      cout<<(temp_string.substr(start_index+1,end_index-start_index-1))<<endl;
      //endDate
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      cout<<(temp_string.substr(start_index+1,end_index-start_index-1))<<endl;
      //title
      start_index=end_index+2;
      end_index=start_index+1;
      while(temp_string[end_index]!='\"'){
        end_index++;
      }
      cout<<temp_string.substr(start_index+1,end_index-start_index-1)<<endl;
    }
    fin.close();
}