#include"Event.h"
#include<string>
#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;
class Calendar {
private:
	Date curDate;
	vector<Event> events;
public:
	void Run();
	void Draw();
	void NextMonth();
	void PreviousMonth();
	void CreateEvent(Date date, string s);
	bool removeEvent(int id);
	vector<Event> getallEvents();
}; 
