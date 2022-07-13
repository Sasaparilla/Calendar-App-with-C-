#include "Event.h"
Event::Event()
{
}
Event::Event(Date d, string _d)
{
	date = d;
	description = _d;
}
void Event::setDate(Date d)
{
	date = d;
}
void Event::setDescription(string s)
{
	description = s;
}
Date Event::getDate()
{
	return date;
}
string Event::getDescription()
{
	return description;
}