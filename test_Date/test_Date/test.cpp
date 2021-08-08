#include<iostream>
using namespace std;

class Date
{
public:
	int GetMonthDays(int year, int month)
	{
		static int MonthDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			return 29;
		}
		return MonthDays[month];
	}
	Date(int year = 0, int month = 1, int day = 1)
	{
		if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day < GetMonthDays(year,month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期" << endl;
		}
	}
	//Data d2(d1)
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	bool operator<(const Date& d)//有隐含的this指针(Date* this,const Date& d)
	{
		if (_year < d._year)
		{
			return true;
		}
		else if (_year == d._year && _month < d._month)
		{
			return true;
		}
		else if(_year == d._year && _month == d._month && _day < d._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator==(const Date& d)
	{
		if (_year == d._year && _month == d._month && _day == d._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator<=(const Date& d)
	{
		///*if (_year < d._year)
		//{
		//	return true;
		//}
		//else if (_year == d._year && _month < d._month)
		//{
		//	return true;
		//}
		//else if (_year == d._year && _month == d._month && _day <= d._day)
		//{
		//	return true;
		//}
		//else
		//{
		//	return false;
		//}*/
		//d1 <= d2 ==> d1.operator(&d1,d2) ==> bool operator<=(Date* this,const Date& d)
		return *this < d || *this == d;//复用上面的代码来实现 this就是d1的地址 *this就是d1
	}
	bool operator>(Date& d)
	{
		return !(*this <= d);
	}
	bool operator>=(Date& d)
	{
		return !(*this < d);
	}
	bool operator!=(Date& d)
	{
		return !(*this == d);
	}

	//d1+day
	//日期加一个天数
	Date operator+(int day)
	{
		Date ret(*this);//用d1拷贝构造一个ret
		ret._day += day;
		while (ret._day > GetMonthDays(ret._year, ret._month))//如果日期的天不合法，就要往月进位
		{
			ret._day -= GetMonthDays(ret._year, ret._month);
			ret._month++;
			if(ret._month == 13)
			{
				ret._year++;
				ret._month = 1;
			}
		}
		return ret;
	}
	Date& operator+=(int day)
	{
		if (day < 0)
		{
			return *this -= -day;
		}
		_day += day;
		while (_day > GetMonthDays(_year,_month))//如果日期的天不合法，就要往月进位
		{
			_day -= GetMonthDays(_year, _month);
			_month++;
			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}
		return *this;
	}
	Date& operator++() //前置++
	{
		*this += 1;
		return *this;//返回加之后的值
	}
	Date operator++(int) //后置++
	{
		Date tmp(*this);
		*this += 1;
		return tmp;//返回加之前的值
	}
	//减
	Date& operator-=(int day)//区别是-=返回自己  -返回的是另外一个值
	{
		if (day < 0)
		{
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0)//不合法，需要处理的条件
		{
			_month--;
			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
			_day += GetMonthDays(_year, _month);
		}
		return *this;
	}
	Date operator-(int day)
	{
		Date ret = *this;
		ret._day -= day;
		while (ret._day <= 0)
		{
			ret._month--;
			if (ret._month == 0)
			{
				ret._year--;
				ret._month == 12;
			}
			ret._day += GetMonthDays(ret._year, ret._month);
		}
		return ret;
	}
	//日期减日期
	int operator-(const Date& d)
	{
		int flag = 1;
		Date max = *this; //拷贝构造
		Date min = d;
		if (*this < d)
		{
			max = d;
			min = *this; //operator= 运算符重载
			flag = -1;//第一个大 就是负数
		}
		int n = 0;
		while (min != max)
		{
			++min; //运算符重载后的++ 尽量调用前置++ 少两次拷贝构造
			++n;
		}
		return n*flag;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1;
	d1.Print();

	Date d2(2021,8,7);
	d2.Print();

	Date d3(2022, 2, 29);
	d3.Print();

	//运算符重载
	cout << (d1 < d2) << endl;
	cout << (d1 > d2) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 != d2) << endl;
	cout << (d1 <= d2) << endl;
	cout << (d1 >= d2) << endl;

	Date d4 = d2 +100;
	d4.Print();

	d1 = d2;//两个对象都已经存在且初始化好了，把d2赋值给d1
	Date d5(d1);//d5还不存在，构造d5时用d1去初始化（拷贝构造）
	Date d6 = d1;//这里也是拷贝构造，用d1去初始化d6

	return 0;
}