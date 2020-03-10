#ifndef JACKREN_PRIORITY_QUEUE
#define JACKREN_PRIORITY_QUEUE

#include "include.hpp"
#include "vector.hpp"
#include "algorithm.hpp"

/*
	Override operator < before using PriorityQueue, default Min-Heap
*/

template<typename T>
class PriorityQueue {
private:
	Vector<T> arr;
	inline static int lSon(int node) {
		return 2 * node + 1;
	}
	inline static int rSon(int node) {
		return 2 * node + 2;
	}
	inline static int father(int node) {
		return (node - 1) >> 1;
	}
	inline T getLastElemAndDelete() {
		T elem = arr[arr.size() - 1];
		arr.pop();
		return elem;
	}
	void percolateUp(int node) {
		T tmpElem = arr[node];
		while (node > 0) {
			int fa = father(node);
			if (arr[fa] < tmpElem)break;
			arr[node] = arr[fa];
			node = fa;
		}
		arr[node] = tmpElem;
	}
	void percolateDown(int node) {
		T tmpElem = arr[node];
		while (1) {
			int sonIndex;
			if (lSon(node) >= arr.size())break;
			else if (rSon(node) >= arr.size())sonIndex = lSon(node);
			else sonIndex = arr[lSon(node)] < arr[rSon(node)] ? lSon(node) : rSon(node);
			if (tmpElem < arr[sonIndex])break;
			arr[node] = arr[sonIndex];
			node = sonIndex;
		}
		arr[node] = tmpElem;
	}
public:
	PriorityQueue() {}
	PriorityQueue(const Vector<T>& initVector) {
		arr = initVector;
		for (int i = (arr.size() >> 1) - 1; i >= 0; i--)percolateDown(i);
	}
	void push(const T& data) {
		arr.append(data);
		percolateUp(arr.size() - 1);
	}
	T top() {
		return arr[0];
	}
	bool empty() const {
		return arr.size() == 0;
	}
	bool pop() {
		if (empty())return false;
		if (arr.size() == 1)getLastElemAndDelete();
		else {
			arr[0] = getLastElemAndDelete();
			percolateDown(0);
		}
		return true;
	}
};

#endif