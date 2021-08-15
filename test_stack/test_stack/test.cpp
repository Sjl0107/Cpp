#include<iostream>
using namespace std;

#include"stack.h"
#include"queue.h"
#include"priority_queue.h"

#include<queue>
#include<functional>//�º�����ͷ�ļ�

//���������� ����֧�ֵ��������� ��Ϊ����ͨ��������һЩ��������
//���֧�ֵ����������� �����Ǻ��Ѻܺõر������������
void test_priority_queue()
{
	//priority_queue<int> pq;//Ĭ�ϴ�����ȼ��� ���ȼ��ߵ��ȳ�
	//�������С�����ȼ��ߣ���β����� �º���
	priority_queue<int, vector<int>, greater<int>> pq;
	pq.push(3);
	pq.push(1);
	pq.push(9);
	pq.push(4);
	pq.push(2);
	
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

//struct��class��c++�У�����Ĭ�ϵķ����޶�����һ������������һ����
//һ������£���Աȫ���У�����struct
//�º��� ����������
//namespace sjl
//{
//	template<class T>
//	struct less
//	{
//		bool operator()(const T& int x1, const T& int x2)
//		{
//			return x1 < x2;
//		}
//	};
//}

void test_sort()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	//Ĭ������ less
	sort(v.begin(), v.end());
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//����
	greater<int> gt;
	sort(v.begin(), v.end(), gt);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	//sjl::test_stack();
	//sjl::test_queue();
	//sjl::test_priority_queue();
	test_sort();

	return 0;
}