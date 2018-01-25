#include<iostream>
#include "Calendar.h"
#include<fstream>
using namespace std;
int main()
{
	calendar cal(2018, 7, 22);
	// change/initialize calendar variable () operator, ie cal(y, m, d); 
		cal.menu(); //One can perform all operations possible by calling menu which has various choices
	// Menu runs infinitely this exit command
	/*
	Alternatively we can call
	cal.display_year(); //to display calendar and events by year
	cal.display_month(); //to display calendar and events by month
	cal.display_day(); //to display events of the day
	cal.set_event(); //creates events on current date
	cal.change_date(); // changes current date
	cal.delete_event(); // deletes events on current date
	*/
}
