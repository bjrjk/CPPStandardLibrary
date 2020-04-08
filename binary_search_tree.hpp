#ifndef JACKREN_BST
#define JACKREN_BST

#include "include.hpp"
#include "vector.hpp"
#include "utility.hpp"

//����������
template<typename T>
class BinarySearchTree {
private:
	BinaryTreeNode<T>* _root; //�ڲ���ָ��
	//����ʵ�庯��
	void _destroy(BinaryTreeNode<T>* ptr) {
		if (!ptr)return;
		_destroy(ptr->l);
		_destroy(ptr->r);
		delete ptr;
	}
	//�ڲ�ǰ���������
	void _preTraversal(BinaryTreeNode<T>* ptr, Vector<T>& storageArr) {
		if (!ptr)return;
		storageArr.append(ptr->data);
		_preTraversal(ptr->l, storageArr);
		_preTraversal(ptr->r, storageArr);
	}
	//�ڲ������������
	void _inTraversal(BinaryTreeNode<T>* ptr, Vector<T>& storageArr) {
		if (!ptr)return;
		_inTraversal(ptr->l, storageArr);
		storageArr.append(ptr->data);
		_inTraversal(ptr->r, storageArr);
	}
	//�ڲ������������
	void _postTraversal(BinaryTreeNode<T>* ptr, Vector<T>& storageArr) {
		if (!ptr)return;
		_postTraversal(ptr->l, storageArr);
		_postTraversal(ptr->r, storageArr);
		storageArr.append(ptr->data);
	}
public:
	//���캯��
	BinarySearchTree() {
		_root = NULL;
	}
	//��������
	~BinarySearchTree() {
		_destroy(_root);
	}
	//�������������뺯��
	void insert(const T& data) {
		if (!_root) {
			_root = new BinaryTreeNode<T>(data);
			return;
		}
		BinaryTreeNode<T>* f=NULL, * s = _root;
		while (s) {
			f = s;
			s = (data < f->data) ? f->l : f->r;
		}
		if (f) {
			if (data < f->data)
				f->l = new BinaryTreeNode<T>(data);
			else f->r = new BinaryTreeNode<T>(data);
			return;
		}
		assert(0);
	}
	//ǰ���������
	void preTraversal(Vector<T>& storageArr) {
		_preTraversal(_root, storageArr);
	}
	//�����������
	void inTraversal(Vector<T>& storageArr) {
		_inTraversal(_root, storageArr);
	}
	//�����������
	void postTraversal(Vector<T>& storageArr) {
		_postTraversal(_root, storageArr);
	}
};

#endif