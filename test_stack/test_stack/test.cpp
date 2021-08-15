#include<iostream>
using namespace std;

#include"stack.h"
#include"queue.h"
#include"priority_queue.h"

#include<queue>
#include<functional>//仿函数的头文件

//容器适配器 都不支持迭代器遍历 因为他们通常都包含一些特殊属性
//如果支持迭代器随便遍历 那他们很难很好地保持自身的性质
void test_priority_queue()
{
	//priority_queue<int> pq;//默认大的优先级高 优先级高的先出
	//如果想让小的优先级高，如何操作？ 仿函数
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

//struct和class在c++中，除了默认的访问限定符不一样，其他都是一样的
//一般情况下，成员全公有，就用struct
//仿函数 （函数对象）
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

	//默认升序 less
	sort(v.begin(), v.end());
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	//降序
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