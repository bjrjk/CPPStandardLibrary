#ifndef NULL
#define NULL 0
#endif

#ifndef JACKREN_NODE
#define JACKREN_NODE

//������ڵ㶨��
template<typename T>
struct Node {
	T data; //������
	Node* next; //ָ����
	//Ĭ�Ϲ��캯��
	Node() :next(NULL) {}
	//���캯������
	Node(const T& data) :data(data), next(NULL) {}
	//���캯������
	Node(const T& data, Node* next) :data(data), next(next) {} 
};


#endif
