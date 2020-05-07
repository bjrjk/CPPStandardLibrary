#ifndef JACKREN_HASHTABLE
#define JACKREN_HASHTABLE

#include "include.hpp"
#include "vector.hpp"
#include "list.hpp"

//哈希表
//使用前，重载==号
template<typename T>
class HashTable {
private:
	int capacity;
	int (*h)(const T&);
	Vector<List<T>> table;
	int hash(const T& v) {
		int pos = h(v);
		assert(0 <= pos && pos < capacity);
		return pos;
	}

public:
	HashTable(int capacity,int (*h)(const T&)):capacity(capacity),h(h) {
		table.reserve(capacity);
	}
	void insert(const T& value) {
		int pos = hash(value);
		table[pos].insert(0, value);
	}
	bool query(const T& value, const T*& dataPtr) {
		int pos = hash(value);
		return table[pos].query(value, dataPtr);
	}
};

#endif
