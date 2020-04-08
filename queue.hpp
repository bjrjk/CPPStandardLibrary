#ifndef JACKREN_QUEUE
#define JACKREN_QUEUE

#include "vector.hpp"


//队列定义
template<typename T>
class Queue {
private:
	Vector<T> _arr; //利用向量作为内部容器承载队列
	int _size,_front; //队列元素个数，队首下标
	//判满
	bool _full() {
		return _size == _arr.size();
	}
	//扩容
	void _enlarge() {
		Vector<T> _newTmpArr;
		_newTmpArr.reserve(_arr.size() * 2);
		for (int i = 0; i < _size; i++) {
			_newTmpArr[i] = _arr[(_front + i) % _arr.size()];
		}
		_arr = _newTmpArr;
		_front = 0;
	}
public:
	//默认构造函数
	Queue():_size(0),_front(0){
		_arr.reserve(10);
	}
	//复制构造函数
	Queue(const Queue& S) {
		_arr = S._arr;
		_size = S._size;
		_front = S._front;
	}
	//重载=运算符，对队列进行浅复制
	Queue& operator = (const Queue& S) {
		_arr = S._arr;
		_size = S._size;
		_front = S._front;
		return *this;
	}
	//队列判空
	bool empty() {
		return _size == 0;
	}
	//在队列中加入元素
	void push(const T& value) {
		if (_full())_enlarge();
		_arr[(_front + _size) % _arr.size()] = value;
		_size++;
	}
	//元素出队列
	bool pop() {
		if (empty())return false;
		_front = (_front + 1) % _arr.size();
		_size--;
		return true;
	}
	//获取队首元素
	T& front() {
		assert(!empty());
		return _arr[_front];
	}
};

#endif