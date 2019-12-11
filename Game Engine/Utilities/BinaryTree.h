/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: BinaryTree.h
Purpose: Container using binary tree
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

#pragma once
#include "BinaryNode.h"

template<class T1, class T2>
class BinaryTree
{
public:
	BinaryTree() : _head(0) {}
	~BinaryTree() {}

	void InsertNode(T1 key, T2 value) {
		BinaryNode<T1, T2> *pCurr = _head, *pPrev = 0;

		while (pCurr) {
			pPrev = pCurr;
			if (key > pCurr->_key) {
				pCurr = pCurr->_rightChild;
			}
			else if (key < pCurr->_key) {
				pCurr = pCurr->_leftChild;
			}
			else {
				pCurr->_value = value;
				return;
			}
		}

		pCurr = new BinaryNode<T1, T2>(key, value);
		if (pPrev) {
			pCurr->SetHeight(pPrev->GetHeight() + 1);
			if (key > pPrev->_key) {
				pPrev->_rightChild = pCurr;
			}
			else {
				pPrev->_leftChild = pCurr;
			}
		}
		else {
			_head = pCurr;
		}
	}

	T2 FindValueByKey(T1 key) {
		BinaryNode<T1, T2> *pCurr = _head;

		while (pCurr) {
			if (pCurr->_key == key) {
				return pCurr->_value;
			}
			else {
				if (key > pCurr->_key) {
					pCurr = pCurr->_rightChild;
				}
				else {
					pCurr = pCurr->_leftChild;
				}
			}
		}
		return 0;
	}
	
	void Clear(BinaryNode<T1, T2> *pHead) {
		if (pHead == 0) return;
		else {
			Clear(pHead->_leftChild);
			Clear(pHead->_rightChild);
		}
		delete pHead;
		pHead = 0;
	}

	BinaryNode<T1, T2> * _head;
};

