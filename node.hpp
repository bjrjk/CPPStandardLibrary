#ifndef NULL
#define NULL 0
#endif

#ifndef JACKREN_NODE
#define JACKREN_NODE

//单链表节点定义
template<typename T>
struct Node {
	T data; //数据域
	Node* next; //指针域
	//默认构造函数
	Node() :next(NULL) {}
	//构造函数重载
	Node(const T& data) :data(data), next(NULL) {}
	//构造函数重载
	Node(const T& data, Node* next) :data(data), next(next) {} 
};


#endif
