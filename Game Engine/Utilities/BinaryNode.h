#pragma once

template<typename T1, class T2>
class BinaryNode
{
public:
	// BinaryNode(): _leftChild(0), _rightChild(0), _key(new T1), _value(new T2), _height(0) {}
	BinaryNode(T1 key, T2 value, int h = 0) : _leftChild(0), _rightChild(0), _key(key), _value(value), _height(h) {}
	~BinaryNode() {};

	BinaryNode * _leftChild;
	BinaryNode * _rightChild;

	T1  _key;
	T2  _value;

	void SetHeight(int h) { _height = h; }
	int  GetHeight() { return _height; }

private:
	int _height;
};

