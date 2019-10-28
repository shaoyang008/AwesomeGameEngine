#include "BinaryTree.h"


template<class T1, class T2>
BinaryTree<T1, T2>::BinaryTree(): _head(0), CompareFunc(0)
{
}

template<class T1, class T2>
BinaryTree<T1, T2>::~BinaryTree()
{
}

template<class T1, class T2>
void BinaryTree<T1, T2>::InsertNode(T1 key, T2 value)
{
	BinaryNode<T1, T2> pCurr = _pHead, pPrev = 0;
	bool LorR = false; // true for right child, false for left child

	while (pCurr) {
		if (cf) {
			LorR = cf(key, pCurr->_key);
		}
		else {
			LorR = key > pCurr->_key;
		}

		pPrev = pCurr;
		if (LorR) {
			pCurr = pCurr->_rightChild;
		}
		else {
			pCurr = pCurr->_leftChild;
		}
	}

	pCurr = new BinaryNode<T1, T2>(key, value);
	if (pPrev) {
		pCurr->SetHeight(pPrev->GetHeight() + 1);
		if (LorR) {
			pPrev->_rightChild = pCurr;
		}
		else {
			pPrev->_leftChild = pCurr->_leftChild;
		}
	}
}

// If found, return a pointer to T2
// else return 0
template<class T1, class T2>
T2 * BinaryTree<T1, T2>::FindValueByKey(T1 key)
{
	BinaryNode<T1, T2> pCurr = _pHead, pPrev = 0;
	bool LorR = false; // true for right child, false for left child

	while (pCurr) {
		if (cf) {
			LorR = cf(key, pCurr->_key);
		}
		else {
			LorR = key > pCurr->_key;
		}

		if (pCurr->_key == key) {
			return &(pCurr->_value);
		}
		else {
			pPrev = pCurr;
			if (LorR) {
				pCurr = pCurr->_rightChild;
			}
			else {
				pCurr = pCurr->_leftChild;
			}
		}
	}
	return 0;
}