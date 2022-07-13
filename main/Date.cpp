#include "Event.h"
#include "ctime"
#include <string>
Date::Date()
{
    time_t t = time(0);
    struct tm* now = localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
}
Date::Date(int a, int b, int c)
{
    day = a;
    month = b;
    year = c;
}
void Date::setDay(int a)
{
    day = a;
}
void Date::setMonth(int a)
{
    month = a;
}
void Date::setYear(int a)
{
    year = a;
}
int Date::GetDay()
{
    return day;
}
int Date::GetMonth()
{
    return month;
}
int Date::GetYear()
{
    return year;
}const std::string Date::DayNames[7] = {
    "Sun",
    "Mon",
    "Tue",
    "Wen",
    "Thu",
    "Fri",
    "Sat"
};

const std::string Date::MonthNames[12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

const int Date::MonthDays[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31,
};

void Date::IncreaseMonth() {
    if (month < 12)
        ++month;
    else {
        month = 1;
        ++year;
    }
}

void Date::DecreaseMonth() {
    if (month > 1)
        --month;
    else {
        month = 12;
        --year;
    }
}