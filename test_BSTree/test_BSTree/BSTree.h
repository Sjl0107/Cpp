#pragma once


//template<class K>
//struct BSTreeNode
//{
//	BSTreeNode<K>* _left;
//	BSTreeNode<K>* _right;
//	K _key;
//	BSTreeNode(const K& key)
//		:_left(nullptr)
//		,_right(nullptr)
//		,_key(key)
//	{}
//};
//
//template<class K>
//class BSTree
//{
//	typedef BSTreeNode<K> Node;
//public:
//	BSTree()
//		:_root(nullptr)
//	{}
//	bool Insert(const K& key)
//	{
//		if (_root == nullptr)
//		{
//			_root = new Node(key);
//			return true;
//		}
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
//			parent = cur;
//			if (cur->_key < key)
//			{
//				//parent = cur;
//				cur = cur->_right;
//			}
//			else if(cur->_key > key)
//			{
//				//parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		cur = new Node(key);
//		if (parent->_key < key)
//		{
//			parent->_right = cur;
//		}
//		else
//		{
//			parent->_left = cur;
//		}
//		return true;
//	}
//
//	bool Find(const K& key)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//				return true;
//			}
//		}
//		return false;
//	}
//
//	bool Erase(const K& key)
//	{
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if(cur->_key > key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				//找到了，开始删除
//				//1、左为空
//				if (cur->_left == nullptr)
//				{
//					if (cur == _root)
//					{
//						_root = _root->_right;
//					}
//					else
//					{
//						if (parent->_right == cur)
//						{
//							parent->_right = cur->_right;
//						}
//						else
//						{
//							parent->_left = cur->_right;
//						}
//					}
//					delete cur;
//				}
//				//2、右为空
//				else if (cur->_right == nullptr)
//				{
//					if (cur == _root)
//					{
//						_root = _root->_left;
//					}
//					else
//					{
//						if (parent->_left == cur)
//						{
//							parent->_left = cur->_left;
//						}
//						else
//						{
//							parent->_right = cur->_left;
//						}
//					}
//					delete cur;
//				}
//				//3、左右都不为空
//				else
//				{
//					Node* rightMinParent = nullptr;
//					Node* rightMin = cur->_right;
//					while (rightMin->_left)
//					{
//						rightMinParent = rightMin;
//						rightMin = rightMin->_left;
//					}
//					//替代删除
//					cur->_key = rightMin->_key;
//					//转换成删除rightMin rightMin左为空
//					if (rightMin == rightMinParent->_left)
//					{
//						rightMinParent->_left = rightMin->_right;
//					}
//					else
//					{
//						rightMinParent->_right = rightMin->_right;
//					}
//					
//					delete rightMin;
//				}
//			}
//		}
//		return false;
//	}
//
//	void _InOrder(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return;
//		}
//		_InOrder(root->_left);
//		cout << root->_key << " ";
//		_InOrder(root->_right);
//	}
//	void InOrder()
//	{
//		_InOrder(_root);
//		cout << endl;
//	}
//
//private:
//	Node* _root;
//};
//
//void Test_BSTree()
//{
//	BSTree<int> t;
//	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
//	for (auto e : a)
//	{
//		t.Insert(e);
//	}
//	t.Erase(4);
//}

template<class K,class V>
struct BSTreeNode
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;

	K _key;
	V _value;
	
	BSTreeNode(const K& key,const V& value)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
		,_value(value)
	{}
};

template<class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	bool Insert(const K& key, const V& value)
	{
		if (_root == nullptr)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_key < key)
			{
				//parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
				{
					//parent = cur;
					cur = cur->_left;
				}
			else
			{
				return false;
			}
		}
		cur = new Node(key,value);
			if (parent->_key < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
		return true;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//找到了，开始删除
				//1、左为空
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = _root->_right;
					}
					else
					{
						if (parent->_right == cur)
						{
							parent->_right = cur->_right;
						}
						else
						{
							parent->_left = cur->_right;
						}
					}
					delete cur;
				}
				//2、右为空
				else if (cur->_right == nullptr)
				{
					if (cur == _root)
					{
						_root = _root->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
				}
				//3、左右都不为空
				else
				{
					Node* rightMinParent = nullptr;
					Node* rightMin = cur->_right;
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}
					//替代删除
					cur->_key = rightMin->_key;
					//转换成删除rightMin rightMin左为空
					if (rightMin == rightMinParent->_left)
					{
						rightMinParent->_left = rightMin->_right;
					}
					else
					{
						rightMinParent->_right = rightMin->_right;
					}

					delete rightMin;
				}
			}
		}
		return false;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " :" << root->_value << endl;
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	Node* _root;
};

void TestBSTree()
{
	BSTree<string, string> dict;
	dict.Insert("sort", "排序");
	dict.Insert("string", "字符串");
	dict.Insert("tree", "树");
	dict.Insert("insert", "插入");

	string str;
	while (cin >> str)
	{
		BSTreeNode<string, string>* ret = dict.Find(str);
		if (ret)
		{
			cout << ret->_value << endl;
		}
		else
		{
			cout << "无此单词" << endl;
		}
	}
}