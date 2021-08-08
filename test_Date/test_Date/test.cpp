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
			cout << "�Ƿ�����" << endl;
		}
	}
	//Data d2(d1)
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	bool operator<(const Date& d)//��������thisָ��(Date* this,const Date& d)
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
		return *this < d || *this == d;//��������Ĵ�����ʵ�� this����d1�ĵ�ַ *this����d1
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
	//���ڼ�һ������
	Date operator+(int day)
	{
		Date ret(*this);//��d1��������һ��ret
		ret._day += day;
		while (ret._day > GetMonthDays(ret._year, ret._month))//������ڵ��첻�Ϸ�����Ҫ���½�λ
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
		while (_day > GetMonthDays(_year,_month))//������ڵ��첻�Ϸ�����Ҫ���½�λ
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
	Date& operator++() //ǰ��++
	{
		*this += 1;
		return *this;//���ؼ�֮���ֵ
	}
	Date operator++(int) //����++
	{
		Date tmp(*this);
		*this += 1;
		return tmp;//���ؼ�֮ǰ��ֵ
	}
	//��
	Date& operator-=(int day)//������-=�����Լ�  -���ص�������һ��ֵ
	{
		if (day < 0)
		{
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0)//���Ϸ�����Ҫ���������
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
	//���ڼ�����
	int operator-(const Date& d)
	{
		int flag = 1;
		Date max = *this; //��������
		Date min = d;
		if (*this < d)
		{
			max = d;
			min = *this; //operator= ���������
			flag = -1;//��һ���� ���Ǹ���
		}
		int n = 0;
		while (min != max)
		{
			++min; //��������غ��++ ��������ǰ��++ �����ο�������
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

	//���������
	cout << (d1 < d2) << endl;
	cout << (d1 > d2) << endl;
	cout << (d1 == d2) << endl;
	cout << (d1 != d2) << endl;
	cout << (d1 <= d2) << endl;
	cout << (d1 >= d2) << endl;

	Date d4 = d2 +100;
	d4.Print();

	d1 = d2;//���������Ѿ������ҳ�ʼ�����ˣ���d2��ֵ��d1
	Date d5(d1);//d5�������ڣ�����d5ʱ��d1ȥ��ʼ�����������죩
	Date d6 = d1;//����Ҳ�ǿ������죬��d1ȥ��ʼ��d6

	return 0;
}