#include "Calendar.h"
#include<sstream>
#include<string>
#include<vector>
#include<iomanip>
#include<ctime>
#include<fstream>

Calendar calender;
void Calendar::Run()
{
	while (true) {
		// for user choice
		cout
			<< "\nN: Show Next Month"
			<< "\tP: Show Previous Month " << "\tI: Show Specific Date "
			<< "\nA: Create An Event" << "\tL: List All Events"
			<< "\tD: Delete An Event" << "\nS: Save All Events"
			<< "\tR: Load Event" << "\tQ: Quit" << "\nInput your command ";
		char ch;
		cin >> ch;
		cout << endl;
		if (ch >= 'a' && ch <= 'z')
			ch += ('A' - 'a');
		// next month
		if (ch == 'N') {
			calender.NextMonth();
			calender.Draw();
		}
		// previous month
		if (ch == 'P') {
			calender.PreviousMonth();
			calender.Draw();
		}
		// any use define date
		if (ch == 'C') {
			cout << "Enter year : ";
			int year;
			cin >> year;
			cout << "Enter month : ";
			int month;
			cin >> month;
			// set current date
			calender.Run();
			// and display
			calender.Draw();
		}
		// add event
		if (ch == 'A') {
			cout << "Enter year : ";
			int year;
			cin >> year;
			cout << "Enter month : ";
			int month;
			cin >> month;
			cout << "Enter day : ";
			int day;
			cin >> day;
			cout << "Enter Description : ";
			string des;
			cin.ignore();
			getline(cin, des);
			Date date(day, month, year);
			// load event in vector
			calender.CreateEvent(date, des);
		}
		// display 4events
		if (ch == 'L') {
			// get all events
			vector<Event> eventlst = calender.getallEvents();
			cout << endl;
			for (int i = 0; i < eventlst.size(); i++) {
				// print each event
				cout << "Event " << (i + 1);
				Event event = eventlst[i];
				cout << "\tDate : " << event.getDate().GetDay() << "-" << event.getDate().GetMonth() << "-" <<
					event.getDate().GetYear();
				cout << "\nDescription : " << event.getDescription() << "\n\n";
			}
		}
		// delete event
		if (ch == 'D') {
			cout << "Enter event ID : ";
			int id;
			cin >> id;
			// if id found
			if (calender.removeEvent(id)) {
				cout << "\nEvent removed \n\n";
			}
			// id not found
			else {
				cout << "\nEvent ID not found \n\n";
			}
		}
		// save event in file
		// day month year [line 1]
		// description [line 2]
		if (ch == 'S') {
			cout << "Enter File Name : ";
			string file;
			cin >> file;
			ofstream out;
			out.open(file.c_str());
			if (out.fail()) {
				cout << "File error.";
			}
			else {
				// get all events
				vector<Event> eventlst = calender.getallEvents();
				// write all event in file
				for (int i = 0; i < eventlst.size(); i++) {
					Event event = eventlst[i];
					out << event.getDate().GetDay() << " " << event.getDate().GetMonth() << " " <<
						event.getDate().GetYear();
					out << endl;
					out << event.getDescription();
					// ney line
					out << "\n";
				}
				out.close();
				cout << "\nData save in file " << file << endl << endl;
			}
		}
		// read from file
		if (ch == 'R') {
			cout << "Enter File Name : ";
			string file;
			cin >> file;
			ifstream in;
			in.open(file.c_str());
			if (in.fail()) {
				cout << "\nFile not found.\n\n";
			}
			else {
				int a, b, c;
				string l;
				// read file until end of the file
				while (!in.eof()) {
					// line for date
					getline(in, l);
					// store in string
					stringstream ss;
					ss << l;
					// get date
					ss >> a;// day
					ss >> b;// month
					ss >> c;// year
					// get description from next line
					getline(in, l);
					Date date(a, b, c);
					// load in vector
					calender.CreateEvent(date, l);
				}
				// get last event id
				// which is error event
				int id = calender.getallEvents().size();
				// delete error event
				calender.removeEvent(id);
				in.close();
				cout << "\nData load from file " << file << endl << endl;
			}
		}
		if (ch == 'Q') {
			break;
		}
	}

}
void Calendar::Draw()
{
	// calculate week day value
	int y, c, m;
	if (curDate.GetDay() == 1 || curDate.GetDay() == 2) {
		y = (curDate.GetYear() - 1) % 100;
		c = (curDate.GetYear() - 1) / 100;
		m = curDate.GetMonth() + 12;
	}
	else {
		y = (curDate.GetYear()) % 100;
		c = (curDate.GetYear()) / 100;
		m = curDate.GetMonth();
	}
	int week = ((y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10) % 7 + 7) % 7;
	// for number of days in month
	int mlen = 0;
	// 31 days for month
	if (curDate.GetMonth() == 1 || curDate.GetMonth() == 3 || curDate.GetMonth() == 5 || curDate.GetMonth() ==
		7 || curDate.GetMonth() == 8 || curDate.GetMonth() == 10 || curDate.GetMonth() == 12) {
		mlen = 31;
	}
	else {
		// for february
		if (m == 2) {
			int year = curDate.GetYear();
			// checking leap year
			bool leap = false;
			if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
				leap = true;
			}
			// for leap year
			if (leap == true) {
				mlen = 29;
			}
			else {
				mlen = 28;
			}
		}
		else {
			mlen = 30;
		}
	}
	// print month name
	cout << "\t" << Date::MonthNames[m - 1];

	// print year
	cout << " " << curDate.GetYear() << endl;
	cout << "****************************" << endl;
	for (int i = 0; i < sizeof Date::DayNames / sizeof Date::DayNames[0]; ++i) {
		cout << Date::DayNames[i] << " ";
	}
	cout << endl;
	// for initial spacees for week day start
	for (int x = 0; x < week; ++x) {
		cout << "    ";
	}


	//Print the date corresponding with the day 
	for (int d = 0; d < mlen; ++d) {
		if (d < 9)

			cout << "0" << d + 1 << "  ";
		else
			cout << d + 1 << "  ";
		++week;
		if (week == 7) {
			week = 0;
			cout << endl;
		}
	}
	cout << endl;
}

void Calendar::NextMonth()
{
	int m = curDate.GetMonth() == 12 ? 1 : (curDate.GetMonth() + 1);
	// if current month is 12 , increase year
	if (curDate.GetMonth() == 12) {
		curDate.setYear(curDate.GetYear() + 1);
	}
	// set next month
	curDate.setMonth(m);
}

void Calendar::PreviousMonth()
{
	// previous month
	int m = curDate.GetMonth() == 1 ? 12 : (curDate.GetMonth() - 1);
	// current month is 1 , decrease year
	if (curDate.GetMonth() == 1) {
		curDate.setYear(curDate.GetYear() - 1);
	}
	// set previous month
	curDate.setMonth(m);
}

void Calendar::CreateEvent(Date date, string s)
{
	// load event
	Event event(date, s);
	events.push_back(event);
}

bool Calendar::removeEvent(int id)
{
	if (events.size() >= id && id > 0) {
		// delete event
		events.erase(events.begin() + id - 1, events.begin() + id);
		return true;
	}
	return false;
}

vector<Event> Calendar::getallEvents()
{
	return events;
}