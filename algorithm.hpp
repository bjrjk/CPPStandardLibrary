#ifndef JACKREN_ALGORITHM
#define JACKREN_ALGORITHM

#include "vector.hpp"
#include "priority_queue.hpp"

template<typename T>
inline void swap(T& v1, T& v2) {
	T tmp = v1;
	v1 = v2;
	v2 = tmp;
}

template<typename T>
inline T min(const T& v1, const T& v2) {
	if (v1 < v2)return v1;
	else return v2;
}

template<typename T>
inline T max(const T& v1, const T& v2) {
	if (v1 < v2)return v2;
	else return v1;
}

template<typename T>
void heapSort(Vector<T>& arr) { //堆排序
	PriorityQueue<T> pq(arr);
	arr.clear();
	while (!pq.empty()) {
		arr.append(pq.top());
		pq.pop();
	}
}

template<typename T>
int _quickSort_partition(Vector<T>& arr, int l, int r) { //快速排序——分区
	T pivot = arr[r];
	while (l != r) {
		while (arr[l] < pivot && l < r)l++;
		if (l < r)arr[r] = arr[l], r--;
		while (pivot < arr[r] && l < r)r--;
		if (l < r)arr[l] = arr[r], l++;
	}
	arr[l] = pivot;
	return l;
}

template<typename T>
void quickSort(Vector<T>& arr, int l, int r) { //快速排序
	if (r <= l)return;
	int pivot = (l + r) >> 1;
	swap(arr[pivot], arr[r]);
	pivot = _quickSort_partition(arr, l, r);
	quickSort(arr, l, pivot - 1);
	quickSort(arr, pivot + 1, r);
}

template<typename T>
void quickSort(Vector<T>& arr) { //快速排序
	quickSort(arr, 0, arr.size() - 1);
}

template<typename T>
int lower_bound(Vector<T>& arr, const T& v) { //二分查找 lower_bound，重载<
	int l = 0, r = arr.size() - 1, mid;
	while (l < r) {
		mid = (l + r) / 2;
		if (arr[mid] < v)l = mid + 1;
		else r = mid;
	}
	return l;
}

template<typename T>
int upper_bound(Vector<T>& arr, const T& v) { //二分查找 upper_bound，重载<
	int l = 0, r = arr.size() - 1, mid;
	while (l < r) {
		mid = (l + r) / 2;
		if (arr[mid] <= v)l = mid + 1;
		else r = mid;
	}
	return l;
}

template<typename T>
int binary_search(Vector<T>& arr, const T& v) { //二分查找 binary_search，重载<
	int l = 0, r = arr.size() - 1, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (arr[mid] < v)l = mid + 1;
		else if (v < arr[mid]) r = mid - 1;
		else return mid;
	}
	return -1;
}

#endif