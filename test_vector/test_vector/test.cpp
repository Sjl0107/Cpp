#include<iostream>
#include<vector>
using namespace std;

void test_vector1()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);

	vector<int> v2(v1);
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << " ";
	}
	cout << endl;

	vector<int> v3;
	v3.push_back(10);
	v3.push_back(20);
	v3.push_back(30);
	v3.push_back(40);

	v1 = v3;
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}

}

void test_vector2()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	//遍历修改数据
	//1、operator[]+size
	for (size_t i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl;
	//2、迭代器
	vector<int>:: iterator it = v1.begin();
	while (it != v1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//3、范围for  -->被编译器替换成迭代器方式支持的
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}

void print_vector(const vector<int>& vt)
{
	//只读
	vector<int>::const_iterator it = vt.begin();
	while (it != vt.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

//三种类型的迭代器
void test_vector3()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//普通正向迭代器 可读可写
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		*it *= 2;//写
		cout << *it << " ";
		++it;
	}
	cout << endl;

	print_vector(v);

	//反向
	vector<int>::reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

void test_vector4()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	cout << v.size() << endl;
	cout << v.capacity() << endl;

}

void test_vector5()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	v.insert(v.begin(), 0);//头插
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.erase(v.begin());//头删
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

//迭代器失效
void test_vector6()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	vector<int>::iterator it = v.begin();

	//v.push_back(5);
	//v.push_back(6);

	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void test_vector7()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	//要求删除容器中所有的偶数
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		//if (*it % 2 == 0)
		//{
		//	v.erase(it);//删除it之后，it就失效了 it的位置不对了，在++it就不行了 vs报错了，是编译器检查的 gcc下没有报错，但是导致结果不对
		//}
		//++it;
		if (*it % 2 == 0)
		{
			it = v.erase(it);//erase会返回删除的it的下一个位置的迭代器
		}
		else
		{
			++it;
		}
	}
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	
}

#include"vector.h"

int main()
{
	sjl::test_vector4();

	return 0;
}