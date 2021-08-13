#pragma once
#include<assert.h>
namespace sjl 
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector()
			:_start(nullptr)
			,_finish(nullptr)
			,_endofstorage(nullptr)
		{}

		//vector(const vector<int>& v)
		//{
		//	_start = new T[v.capacity()];
		//	_finish = _start;
		//	_endofstorage = _start + v.capacity();
		//
		//	for (size_t i = 0; i < v.size(); ++i)
		//	{
		//		*_finish = v[i];
		//		++_finish;
		//	}
		//}
		vector(const vector<int>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			for (const auto& e : v)
			{
				push_back(e);
			}
		}

		vector<T>& operator=(const vector<T>& v)
		{
			if (this != &v)
			{
				delete[] _start;
				_start = new T[v.capacity()];
				memcpy(_start, v._start, sizeof(T) * v.size());
			}
			// 
			//swap(_start, v._start);
			//swap(_finish, v._finish);
			//swap(_endofstorage, v._endofstorage);
			
			//swap(v);

			return *this;
		}

		void swap(vector<T>& v)
		{
			::swap(_start, v._start);
			::swap(_finish, v._finish);
			::swap(_endofstorage, v._endofstorage);
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					//memcpy(tmp, _start, sizeof(T) * size());
					//memcpy按字节拷贝，是浅拷贝
					for (size_t i = 0; i < sz; ++i)
					{
						tmp[i] = _start[i];//调用的是T的operator=，是深拷贝
					}
					delete[] _start;					
				}
				_start = tmp;
				_finish = tmp + sz;
				_endofstorage = tmp + n;
			}
		}

		void resize(size_t n, const T& val = T())
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		void push_back(const T& x)
		{
			//if (_finish == _endofstorage)
			//{
			//	size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			//	reserve(newcapacity);
			//}
			//*_finish = x;
			//++_finish;
			insert(_finish, x);
		}

		void pop_back()
		{
			//assert(_start < _finish);
			//--_finish;
			erase(_finish - 1);
		}

		void insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			if (_finish == _endofstorage)
			{
				size_t n = pos - _start;//迭代器失效
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
				pos = _start + n;//需要重新计算pos
			}
			iterator end = _finish - 1;
			while(end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
		}

		iterator erase(iterator pos)
		{
			assert(pos < _finish);
			iterator it = pos;
			while (it <= _finish)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;
			return pos;
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
	
	void print_vector(const vector<int>& v)
	{
		vector<int>::const_iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_vector1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}

	void test_vector2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		
		v.insert(v.begin(), 0);

		print_vector(v);

		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				it = v.erase(it);
			}
			else
			{
				++it;
			}
		}
		print_vector(v);
	}

	void test_vector3()
	{
		vector<int> v;
		v.reserve(10);
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		print_vector(v);
		cout << v.size() << endl;
		cout << v.capacity() << endl;

		v.resize(4);
		print_vector(v);
		cout << v.size() << endl;
		cout << v.capacity() << endl;

		v.resize(8,8);
		print_vector(v);
		cout << v.size() << endl;
		cout << v.capacity() << endl;
		
		v.resize(12,12);
		print_vector(v);
		cout << v.size() << endl;
		cout << v.capacity() << endl;
	}

	void test_vector4()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);

		vector<int> v2(v1);

		for (size_t i = 0; i < v1.size(); ++i)
		{
			cout << v1[i] << " ";
		}
		cout << endl;

		for (size_t i = 0; i < v2.size(); ++i)
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
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}
