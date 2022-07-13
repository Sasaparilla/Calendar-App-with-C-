#include"Date.h"
#include<string>
using namespace std;
class Event {
private:
	Date date;
	string description;
public:
	Event();
	Event(Date d, string _d);
	void setDate(Date d);
	void setDescription(string s);
	Date getDate();
	string getDescription();
};