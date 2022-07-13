#include<iostream>
#include<fstream>
#include"Calendar.h"
using namespace std;
int main() {
	Calendar calender;
	calender.Draw();
	calender.Run();

	system("pause");
	return 0;
}