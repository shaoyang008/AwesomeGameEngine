#include "BinaryNode.h"

template<class T1, class T2>
BinaryNode<T1, T2>::BinaryNode(): _leftChild(0), _rightChild(0), _key(new T1), _value(new T2), _height(0)
{

}

template<class T1, class T2>
BinaryNode<T1, T2>::BinaryNode(T1 key, T2 value, int h = 0) : _leftChild(0), _rightChild(0), _key(key), _value(value), _height(h)
{

}

template<class T1, class T2>
BinaryNode<T1, T2>::~BinaryNode()
{
}
