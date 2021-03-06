#pragma once

template<class T>

struct AVLTreeNode

{

	AVLTreeNode(const T& data = T())

		: _pLeft(nullptr)

		, _pRight(nullptr)

		, _pParent(nullptr)

		, _data(data)

		, _bf(0)

	{}



	AVLTreeNode<T>* _pLeft;

	AVLTreeNode<T>* _pRight;

	AVLTreeNode<T>* _pParent;

	T _data;

	int _bf;  // 节点的平衡因子

};







// AVL: 二叉搜索树 + 平衡因子的限制

template<class T>

class AVLTree

{

	typedef AVLTreeNode<T> Node;

public:

	AVLTree()

		: _pRoot(nullptr)

	{}



	bool Insert(const T& data)

	{

		// 先按照二叉搜索树的方式进行插入

		if (nullptr == _pRoot)

		{

			_pRoot = new Node(data);

			return true;

		}



		// 按照二叉搜索树特性：找待插入节点在树中的位置

		// 并保存其双亲

		Node* pCur = _pRoot;

		Node* pParent = nullptr;

		while (pCur)

		{

			pParent = pCur;

			if (data < pCur->_data)

				pCur = pCur->_pLeft;

			else if (data > pCur->_data)

				pCur = pCur->_pRight;

			else

				return false;

		}



		// 插入新节点

		pCur = new Node(data);

		if (data < pParent->_data)

			pParent->_pLeft = pCur;

		else

			pParent->_pRight = pCur;

		pCur->_pParent = pParent;



		while (pParent)

		{

			// 更新pParent的平衡因子

			if (pCur == pParent->_pLeft)

				pParent->_bf--;

			else

				pParent->_bf++;



			if (0 == pParent->_bf)

				break;

			else if (-1 == pParent->_bf || 1 == pParent->_bf)

			{

				pCur = pParent;

				pParent = pCur->_pParent;

			}

			else

			{

				// pParent->_bf: 2 || -2

				// pParent的节点失去平衡

				if (2 == pParent->_bf)

				{

					// 右子树高-->最后必须左单旋

					if (1 == pCur->_bf)

						RotateL(pParent);

					else

						RotateRL(pParent);

				}

				else

				{

					if (-1 == pCur->_bf)

						RotateR(pParent);

					else

						RotateLR(pParent);

				}



				break;

			}

		}



		return true;

	}



	void InOrder()

	{

		_InOrder(_pRoot);

	}



	Node* LeftMost()

	{

		if (nullptr == _pRoot)

			return nullptr;



		Node* pCur = _pRoot;

		while (pCur->_pLeft)

			pCur = pCur->_pLeft;



		return pCur;

	}



	Node* RightMost()

	{

		if (nullptr == _pRoot)

			return nullptr;



		Node* pCur = _pRoot;

		while (pCur->_pRight)

			pCur = pCur->_pRight;



		return pCur;

	}



	bool IsAVLTree()

	{

		return _IsAVLTree(_pRoot);

	}



private:

	// 验证二叉搜索树是否为有效的

	bool _IsAVLTree(Node* pRoot)

	{

		if (nullptr == pRoot)

			return true;



		int leftHeight = _Height(pRoot->_pLeft);

		int rightHeight = _Height(pRoot->_pRight);



		if (abs(rightHeight - leftHeight) > 1 ||

			rightHeight - leftHeight != pRoot->_bf)

			return false;



		return _IsAVLTree(pRoot->_pLeft) && _IsAVLTree(pRoot->_pRight);

	}



	size_t _Height(Node* pRoot)

	{

		if (nullptr == pRoot)

			return 0;



		size_t leftHeight = _Height(pRoot->_pLeft);

		size_t rightHeight = _Height(pRoot->_pRight);



		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

	}





	void RotateR(Node* pParent)

	{

		Node* pSubL = pParent->_pLeft;

		Node* pSubLR = pSubL->_pRight;



		// 改变pParent和pSubL孩子的指向

		pParent->_pLeft = pSubLR;

		if (pSubLR)

			pSubLR->_pParent = pParent;



		pSubL->_pRight = pParent;



		// 更新pParent和pSubL的双亲

		Node* pPParent = pParent->_pParent;

		pParent->_pParent = pSubL;

		pSubL->_pParent = pPParent;



		// 更新原pParent双亲的左||右指针域指向

		if (nullptr == pPParent)

		{

			_pRoot = pSubL;

		}

		else

		{

			if (pParent == pPParent->_pLeft)

				pPParent->_pLeft = pSubL;

			else

				pPParent->_pRight = pSubL;

		}



		pParent->_bf = pSubL->_bf = 0;

	}



	void RotateL(Node* pParent)

	{

		Node* pSubR = pParent->_pRight;

		Node* pSubRL = pSubR->_pLeft;



		pParent->_pRight = pSubRL;

		if (pSubRL)

			pSubRL->_pParent = pParent;



		pSubR->_pLeft = pParent;

		Node* pPParent = pParent->_pParent;

		pParent->_pParent = pSubR;

		pSubR->_pParent = pPParent;



		if (nullptr == pPParent)

		{

			_pRoot = pSubR;

		}

		else

		{

			if (pParent == pPParent->_pLeft)

				pPParent->_pLeft = pSubR;

			else

				pPParent->_pRight = pSubR;

		}



		pParent->_bf = pSubR->_bf = 0;

	}



	void RotateRL(Node* pParent)

	{

		Node* pSubR = pParent->_pRight;

		Node* pSubRL = pSubR->_pLeft;

		int bf = pSubRL->_bf;



		RotateR(pParent->_pRight);

		RotateL(pParent);



		// 更新部分节点的平衡因子

		if (bf == -1)

			pSubR->_bf = 1;

		else if (bf == 1)

			pParent->_bf = -1;

	}



	void RotateLR(Node* pParent)

	{

		Node* pSubL = pParent->_pLeft;

		Node* pSubLR = pSubL->_pRight;

		int bf = pSubLR->_bf;



		RotateL(pParent->_pLeft);

		RotateR(pParent);

		if (-1 == bf)

			pParent->_bf = 1;

		else if (1 == bf)

			pSubL->_bf = -1;

	}



	void _InOrder(Node* pRoot)

	{

		if (pRoot)

		{

			_InOrder(pRoot->_pLeft);

			cout << pRoot->_data << " ";

			_InOrder(pRoot->_pRight);

		}

	}



private:

	Node* _pRoot;

};
