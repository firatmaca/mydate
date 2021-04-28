#include "Date.h"
#include "string.h"
#include <iostream>
#include <sstream>
#include <vector>

static  int ay�ngunleri[] = { 404,31,28,31,30,31,30,31,31,30,31,30,31 };

Date::Date() : gun(1), ay(1), y�l(1900)
{

}
Date::Date(int d, int m, int y): gun(d) , ay(m) , y�l (y) {

	if (y < year_base && y > random_max_year) {
		std::cout << year_base << "-" << random_max_year << "Aras�nda Y�l Giriniz" << '\n';
	}
	else if (m < 1 && m > 12)
	{
		std::cout << 1 << "-" << 12 << "Aras�nda Ay Giriniz" << '\n';
	}
	else if (d < 1 && d > ay�ngunleri[m])
	{
		std::cout << 1 << "-" << ay�ngunleri[m] << "Aras�nda G�n Giriniz" << '\n';
	}
	else {
		if (isleap(y))
			ay�ngunleri[2] = 29;
		else
			ay�ngunleri[2] = 28;

	}
}

Date::Date (const char* p) {

	std::string s{ p };
	int day, month, year;
	std::string delimiter = "/";
	size_t pos = 0;
	std::string token;
	std::vector <std::string> vec;
	for(int i = 0 ; i<3 ; ++i){
		pos = s.find(delimiter);
	    token = s.substr(0, pos);
		vec.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	day = stoi(vec.at(0));
	month = stoi(vec.at(1));
	year = stoi(vec.at(2));
	set_year(year);
	set_month(month);
	set_month_day(day);
}
Date:: Date(std::time_t timer){

	tm* tm = localtime(&timer);
	set_year(year_base + tm->tm_year);
	set_month (tm->tm_mon +1);
	set_month_day(tm->tm_mday);
}

int  Date:: get_month_day()const {
	return gun;
}

int Date::get_month()const {
	return ay;
}

int Date:: get_year()const {
	return y�l;
}

Date::WeekDay Date::get_week_day()const {
 	Date f;
	Date date2 { *this };
	int x = date2 - f;
	int mod = x % 7;
	return WeekDay(mod +1);
}

Date& Date::set_month_day(int day) {
	if (day < 1 || day > ay�ngunleri[ay])
	{
		std::cout << 1 << "-" << ay�ngunleri[ay] << "Aras�nda G�n Giriniz" << '\n';
		exit(EXIT_FAILURE);
	}
	gun = day;

	return *this;

}

Date& Date :: set_month(int month) {
	if (month < 1 || month >12) {
		std::cout << 1 << "-" << 12 << "Aras�nda Ay Giriniz" << '\n';
		exit(EXIT_FAILURE);
	}

	ay = month;

	return *this;

}

Date& Date::set_year(int year) {
	if (year < year_base ) {
		std::cout << year_base << "Degerinden B�y�k Yil Giriniz" << '\n';
		exit(EXIT_FAILURE);
	}
	if (isleap(year))
		ay�ngunleri[2] = 29;
	else
		ay�ngunleri[2] = 28;

	y�l = year;

	return *this;

}

Date& Date::set(int day, int mon, int year) {
	set_month_day(day);
	set_month(mon);
	set_year(year);
	return *this;
}
 Date Date:: random_date() {
	 srand(time(NULL));
	 int r_gun, r_ay, r_y�l;
	 r_y�l = random_min_year + (rand() % (random_max_year - random_min_year));
	 r_ay = rand() % 12 + 1;
	 if (isleap(r_y�l)) {
		 ay�ngunleri[2] = 29;
		 r_gun = rand() % (ay�ngunleri[r_ay]) + 1;
	 }
	 else {
		 ay�ngunleri[2] = 28;
		 r_gun = rand() % (ay�ngunleri[r_ay]) + 1;
	 }
	 return Date(r_gun, r_ay, r_y�l);
}

constexpr bool Date::isleap(int year) {
	
	if (year % 400 == 0)
		return false; 

	if (year % 4 == 0) {
		return true;
	}


	
	return false;
}
int Date:: get_year_day()const {
	int toplam { gun };
	if (isleap(y�l))
		ay�ngunleri[2] = 29;
	else
		ay�ngunleri[2] = 28;
	for (int i = 1; i < ay; ++i) {
		toplam += ay�ngunleri[i];
	}

	return toplam;
}

Date& Date:: operator+=(int day) {

	Date f;
	Date date2{ *this };
	int totoal_day = date2 - f;
	totoal_day += day;
	int temp_y�l = year_base;
	int temp_day{};
	while (1) {
		if (isleap(temp_y�l)) {
			temp_day = 366;
		}
		else {
			temp_day = 365;
		}
		
		totoal_day -= temp_day;
		++temp_y�l;
		if (temp_day > totoal_day) {
			if (isleap(temp_y�l)) {
				ay�ngunleri[2] = 29;
			}
			else {
				ay�ngunleri[2] = 28;
			}
			int i{}, j{1};
			for (; i < totoal_day- ay�ngunleri[j]; ++j)
			{
				i += ay�ngunleri[j];
			}
			set_month(j);
			set_month_day(totoal_day - i+1);
			break;
		}
	}
	set_year(temp_y�l);

	return *this;
}

Date& Date::operator++()
{
	return (*this) += 1;
}

Date Date::operator++(int)
{
	Date temp{ *this };
	(*this)+=(1);
	return temp;
}

Date& Date:: operator-=(int day) {

	Date f;
	Date date2{ *this };
	int totoal_day = date2 - f;
	totoal_day -= day;
	int temp_y�l = year_base;
	int temp_day{};
	while (1) {
		if (isleap(temp_y�l)) {
			temp_day = 366;
		}
		else {
			temp_day = 365;
		}
		++temp_y�l;
		totoal_day -= temp_day;

		if (temp_day > totoal_day) {
			if (isleap(temp_y�l)) {
				ay�ngunleri[2] = 29;
			}
			else {
				ay�ngunleri[2] = 28;
			}
			int i{}, j{ 1 };
			for (; i < totoal_day-ay�ngunleri[j]; ++j)
			{
				i += ay�ngunleri[j];
			}
			set_month(j);
			set_month_day(totoal_day - i+1);
			break;
		}

	}
	set_year(temp_y�l);
	return *this;

}

Date& Date:: operator--() {

	return (*this)-=1;
}

int operator-(const Date& d1, const Date& d2) 
{
	int fark1{d1.get_year_day()};
	if ( (d1.get_year() - Date::year_base ) > 0) {
		for (int i = Date::year_base; i < d1.get_year(); ++i)
		{
			if (Date::isleap(i)) {
				fark1 += 366;
			}
			else
			{
				fark1 += 365;
			}
		}
	}
	int fark2{ d2.get_year_day() };
	if ((d2.get_year() - Date::year_base) > 0) {
		for (int i = Date::year_base; i < d2.get_year(); ++i)
		{
			if (Date::isleap(i)) {
				fark2 += 366;
			}
			else
			{
				fark2 += 365;
			}
		}
	}
	
	return fark1- fark2;

}
Date Date:: operator-(int day)const {
	return Date{ *this } +=  (-day);
}

Date Date:: operator--(int) {
	Date temp {*this};
	--(*this);
	return temp;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	return os << " " << date.get_year() <<  " " <<  date.get_month()<< " " << date.get_month_day()  ;
}

std::istream& operator >>(std::istream& is, Date& date) {
	return is >> date.gun >> date.ay >> date.y�l ;
}

std::ostream& operator<<(std::ostream& os, const Date::WeekDay& r)
{
	static const char* const wdays[] = { "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday" };
	return os << wdays[static_cast<int>(r)];
}