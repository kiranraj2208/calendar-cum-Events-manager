#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
std::string get_string();
int dates[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
string months[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
void read_from_file();
class calendar{
	private:
		int dd;
		int mm;
		int yy;
		int h;
		static int count;
		string Event;
		void write_into_file(calendar);
		void search_event(int m, int d = 0);
		friend void read_from_file();
		friend bool compare(calendar, calendar);
		static void init()
		{
			if(count++ == 0)
			read_from_file();
		}	
		bool leap(int y);
		void final_write();
		int get_day();
	public:
		calendar(int y = 2018, int m = 1, int d = 1):yy(y), mm(m), dd(d){init();
		dates[2] = (leap(yy))?29 : 28;
		if(mm > 12 || mm < 1 || dd > dates[mm] || dd < 1)
		{
			cout << "Invalid Entry of date\n";
			exit(0);
		}
		}
		void display_month(int);
		void display_day();
		void display_year();
		void operator()(int y, int m, int d);
		void set_event();
		void menu();
		void change_date();
		void delete_event(int,int,int);
		~calendar(){}
};
int calendar::count = 0;
vector<calendar>events;
void calendar::operator()(int y = 2018, int m = 1, int d = 1)
{
	yy = y;
	mm = m;
	dd = d;
	dates[2] = (leap(yy))? 29: 28;
	if(mm > 12 || mm < 1 || dd > dates[mm] || dd < 1)
		{
			cout << "Invalid Entry of date\n";
			exit(0);
		}
}
bool compare(calendar b, calendar c)
{
	if(b.yy < c.yy)
	return true;
	else if (b.yy > c.yy)
	return false;
	else if(b.mm < c.mm)
	return true;
	else if(b.mm > c.mm)
	return false;
	else if (b.dd < c.dd)
	return true;
	else 
	return false;
}
int calendar::get_day()
{
	int m = mm;
	int y = yy;
	if(mm == 1)
	{
		m = 13;
		y--;
	}
	if(mm == 2)
	{
		m = 14;
		y--;
	}
	int q = dd;
	int k = y % 100;
	int j = y / 100;
	h = q + 13*(m+1)/5 + k + k/4 + j/4 + 5*j;
	h = h % 7;
	return h;
}
bool calendar::leap(int y)
{
	if(yy%100 == 0 && yy%400 == 0 || yy%4 == 0 && yy%100 != 0)
	return true;
	return false;
}
void calendar::display_month(int m = 0)
{
	int mon = mm;
	if(m != 0)
	mm = m;
	else
	m = mm;
	int dat = dd;
	dd = 1;
	int d = get_day();
	int i = (d+6) % 7;
	dates[2] = (leap(yy))? 29: 28;
	cout << "\t\t" << months[m] << " " << yy << endl;
	cout << "---------------------------------------------------\n";
	cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSat\n";
	cout << "---------------------------------------------------\n";
	for(int j = 0; j < i; j++)
	cout << "   \t";
	for(int j = 1; j <= dates[m]; j++)
	{
		cout << j << "\t";
		if((j+i)%7 == 0)
		cout << endl;
	}
	cout << "\n---------------------------------------------------\n\n";
	search_event(m);
	mm = mon;
	dd = dat;
}
void calendar::display_year()
{
	for(int i = 1; i <= 12; i++)
		display_month(i);
}
void calendar::display_day(){
	int day = (get_day()+6)%7;
	cout << yy << "/"<< mm << "/" << dd << ":" << days[day] << endl;
	search_event(mm, dd);
}
void read_from_file()
{
	fstream file("events_file.txt", ios::in);
	if(file == NULL)
	{
		file.open("events_file.txt", ios::out);
		file.close();
		return;
	}
	calendar cal;
	events.clear();
	int d, m, y;
	string E;
	while(file >> y)
	{
		file >> m;
		file >> d;
		file.ignore();
		getline(file, E);
		cal.dd = d;
		cal.mm = m;
		cal.yy = y;
		cal.Event = E;
		events.push_back(cal);
	}
	sort(events.begin(), events.end(), compare);
	file.close();
}
void calendar::write_into_file(calendar cal)
{
	fstream file("events_file.txt", ios::out | ios::app);
	file << cal.yy << " ";
	file << cal.mm << " ";
	file << cal.dd << endl;
	file << cal.Event << endl;
	file.close();
}
void calendar::set_event()
{
	string str;
	int n;
		cout << "Enter the event on the entered date:";
		cin.ignore();
		getline(cin, str);
		Event = str;
		events.push_back(*this);
		sort(events.begin(), events.end(), compare);
}
void calendar::final_write()
{
	fstream file("events_file.txt", ios::out);
	file.clear();	
	file.close();
	sort(events.begin(), events.end(), compare);
	for(vector<calendar>::iterator it = events.begin(); it != events.end(); it++)
	write_into_file(*it);
}
void calendar::search_event(int m, int d)
{
	int flag = 0;
	for(vector<calendar>::iterator it = events.begin(); it != events.end(); it++)
	{
		if(it->yy == yy && it->mm == m && d == 0)
		{
			string s = months[m];
			cout << s.substr(0, 3) << " " << (it)->dd << ":" << it->Event << endl;
			flag = 1;
		}
		else if(it->yy == yy && it->mm == mm && d != 0 && it->dd == d)
		{
			cout << it->Event << endl;
			flag = 1;
		}
	}
		if(flag == 0)
		cout << "No Events\n";
		cout << endl;
}
void calendar::change_date()
{
	int y, m, d;
	cout << "Enter the year, month, date:";
	cin >> y >> m >> d;
	this->operator()(y, m, d);
}
void calendar::delete_event(int y = 0, int m = 0, int d = 0)
{
	int flag = 0;
	if(y == 0 || m == 0 || d == 0)
	{
		cout << "Enter the year, month, day:";
		cin >> y >> m >> d;
	}
	for(vector<calendar>::iterator it = events.begin(); it != events.end(); it++)
	{
		if(it->yy == y && it->mm == m && it->dd == d)
		{
			events.erase(it);
			cout << "Events deleted\n";
			flag = 1;
		}
	}
	if(flag == 0)
	cout << "No Events\n";	
}
void calendar::menu()
{
	cout << "\nCurrent date:" << yy << "/" << mm << "/" << dd << endl;
	cout << "Menu\n";
	cout << "\t1.Display events of current year.\n";
	cout << "\t2.Display events of current month.\n";
	cout << "\t3.Display events of current day.\n";
	cout << "\t4.Change date\n";
	cout << "\t5.Set event on current day.\n";
	cout << "\t6.Set event on other day.\n";
	cout << "\t7.Delete events on current day.\n";
	cout << "\t8.Delete events on other day.\n";
	cout << "\t9.Exit(Please terminate program only by this method).\n";
	short int choice;
	cin >> choice;
	calendar cal = *this;
	switch(choice)
	{
		case 1:display_year();break;
		case 2:display_month();break;
		case 3:display_day();break;
		case 4:change_date();break;
		case 5:set_event();break;
		case 6:change_date();set_event();this->operator()(cal.yy, cal.mm, cal.dd);break;
		case 7:delete_event(this->yy, this->mm, this->dd);break;
		case 8:delete_event();break;
		default:final_write();exit(0);
	}
	menu();
}
