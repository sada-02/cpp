#include "date.h"
#include "bits/stdc++.h"
using namespace std;

Date::Date(int day , int month , int year) : m_day {day} , m_month {month} , m_year {year} {
    cout<<"Constructor was called"<<endl;
}

void Date::printDate() const {
    cout<<"Day : "<<m_day<<" Month : "<<m_month<<" Year  : "<<m_year<<endl;
}