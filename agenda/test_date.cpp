#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include "Date.hpp"
#include <iostream>
using namespace std;
const int MAXN=100;
int main(){
	int m_year,m_month,m_day,m_hour,m_minute;
	string temp="1800-01-01/00:00";
	Date a(temp);
	cout<<Date::dateToString(a)<<endl;
	cout<<a.getYear()<<endl;
	cout<<a.getMonth()<<endl;
	cout<<a.getDay()<<endl;
	cout<<a.getHour()<<endl;
	cout<<a.getMinute()<<endl;
}