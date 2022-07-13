#include <string>
class Date {
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(int a, int b, int c);
	void setDay(int a);
	void setMonth(int a);
	void setYear(int a);
	void IncreaseMonth();
	void DecreaseMonth();
	static const std::string DayNames[7]; //all object have weekdays
	static const std::string MonthNames[12]; //*************** Months
	static const int MonthDays[12]; //*************** Days
	int GetDay();
	int GetMonth();
	int GetYear();
};