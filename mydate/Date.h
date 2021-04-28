#ifndef DATE_H
#define DATE_H
#include <iosfwd>
#include <ctime>



class Date {
public:

	static constexpr int year_base = 1900;  
	static constexpr int random_min_year = 1940;  
	static constexpr int random_max_year = 2020;  
	enum class WeekDay { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }; 
	Date(); 
	Date(int d, int m, int y);  
	Date(const char* p);  
	Date(std::time_t timer); 
	int get_month_day()const; 
	int get_month()const; 
	int get_year()const; 
	int get_year_day()const; 
	WeekDay get_week_day()const; 

	Date& set_month_day(int day); 
	Date& set_month(int month); 
	Date& set_year(int year); 
	Date& set(int day, int mon, int year); 
	Date operator-(int day)const; 
	Date& operator+=(int day); 
	Date& operator-=(int day); 
	Date& operator++(); 
	Date operator++(int); 
	Date& operator--(); 
	Date operator--(int); 

	static Date random_date(); 
	static constexpr bool isleap(int y); 

	friend bool operator<(const Date& x, const Date& y) { 
		if (y.yýl < x.yýl)
			return false;
		else if ( y.yýl == x.yýl)
		{
			if (y.ay < x.ay) {
				return false;
			}
			else if(x.ay == y.ay)
			{
				if (y.gun < x.gun)
				{
					return false;
				}
			}
		} 
			
		
		return true;
	}
	
	friend bool operator==(const Date& x, const Date& y) { 
		if (x.gun == y.gun && x.ay == y.ay && x.yýl == y.yýl)
			return true;
		return false;
	}


	friend int operator-(const Date& d1, const Date& d2);
	friend std::ostream& operator<<(std::ostream& os, const Date& date); 
	friend std::istream& operator>>(std::istream& is, Date& date); 
	friend std::ostream& operator<<(std::ostream& os, const Date::WeekDay& wd);
private :
	int gun;
	int ay;
	int yýl;

};

inline bool operator>(const Date& x, const Date& y) { 
	return  y < x;
}

inline bool operator<=(const Date& x, const Date& y) { 
  
	return !(y < x);

}

inline bool operator>=(const Date& x , const Date& y) { 
	return !(x < y);
}

inline bool operator!=(const Date& x, const Date& y) {
	return !(x == y);
}

inline Date operator+(const Date& date, int n) 
{
	return  Date{ date } += n;
}
inline Date operator+(int n, const Date& date) 
{
	return Date{ date } += n;
}

inline Date::WeekDay& operator++(Date::WeekDay& r) 
{
	return r = (r == Date::WeekDay::Saturday) ? Date::WeekDay::Sunday : static_cast<Date::WeekDay>((static_cast<int>(r) + 1));

}
inline Date::WeekDay operator++(Date::WeekDay& r, int) 
{
	Date::WeekDay temp{ r };
	++r;
	return temp;
}
inline Date::WeekDay& operator--(Date::WeekDay& r) 
{
	return r = (r == Date::WeekDay::Sunday) ? Date::WeekDay::Saturday : static_cast<Date::WeekDay>((static_cast<int>(r) - 1));

}
inline Date::WeekDay operator--(Date::WeekDay& r, int) 
{
	Date::WeekDay temp{ r };
	--r;
	return temp;
}


#endif