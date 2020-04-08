#ifndef JACKREN_BST
#define JACKREN_BST

#include "include.hpp"
#include "vector.hpp"
#include "utility.hpp"

//二叉搜索树
template<typename T>
class BinarySearchTree {
private:
	BinaryTreeNode<T>* _root; //内部根指针
	//析构实体函数
	void _destroy(BinaryTreeNode<T>* ptr) {
		if (!ptr)return;
		_destroy(ptr->l);
		_destroy(ptr->r);
		delete ptr;
	}
	//内部前序遍历函数
	void _preTraversal(BinaryTreeNode<T>* ptr, Vector<T>& storageArr) {
		if (!ptr)return;
		storageArr.append(ptr->data);
		_preTraversal(ptr->l, storageArr);
		_preTraversal(ptr->r, storageArr);
	}
	//内部中序遍历函数
	void _inTraversal(BinaryTreeNode<T>* ptr, Vector<T>& storageArr) {
		if (!ptr)return;
		_inTraversal(ptr->l, storageArr);
		storageArr.append(ptr->data);
		_inTraversal(ptr->r, storageArr);
	}
	//内部后序遍历函数
	void _postTraversal(BinaryTreeNode<T>* ptr, Vector<T>& storageArr) {
		if (!ptr)return;
		_postTraversal(ptr->l, storageArr);
		_postTraversal(ptr->r, storageArr);
		storageArr.append(ptr->data);
	}
public:
	//构造函数
	BinarySearchTree() {
		_root = NULL;
	}
	//析构函数
	~BinarySearchTree() {
		_destroy(_root);
	}
	//二叉搜索树插入函数
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
	//前序遍历函数
	void preTraversal(Vector<T>& storageArr) {
		_preTraversal(_root, storageArr);
	}
	//中序遍历函数
	void inTraversal(Vector<T>& storageArr) {
		_inTraversal(_root, storageArr);
	}
	//后序遍历函数
	void postTraversal(Vector<T>& storageArr) {
		_postTraversal(_root, storageArr);
	}
};

#endif