#ifndef JACKREN_QUEUE
#define JACKREN_QUEUE

#include "vector.hpp"


//���ж���
template<typename T>
class Queue {
private:
	Vector<T> _arr; //����������Ϊ�ڲ��������ض���
	int _size,_front; //����Ԫ�ظ����������±�
	//����
	bool _full() {
		return _size == _arr.size();
	}
	//����
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
	//Ĭ�Ϲ��캯��
	Queue():_size(0),_front(0){
		_arr.reserve(10);
	}
	//���ƹ��캯��
	Queue(const Queue& S) {
		_arr = S._arr;
		_size = S._size;
		_front = S._front;
	}
	//����=��������Զ��н���ǳ����
	Queue& operator = (const Queue& S) {
		_arr = S._arr;
		_size = S._size;
		_front = S._front;
		return *this;
	}
	//�����п�
	bool empty() {
		return _size == 0;
	}
	//�ڶ����м���Ԫ��
	void push(const T& value) {
		if (_full())_enlarge();
		_arr[(_front + _size) % _arr.size()] = value;
		_size++;
	}
	//Ԫ�س�����
	bool pop() {
		if (empty())return false;
		_front = (_front + 1) % _arr.size();
		_size--;
		return true;
	}
	//��ȡ����Ԫ��
	T& front() {
		assert(!empty());
		return _arr[_front];
	}
};

#endif