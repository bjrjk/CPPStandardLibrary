#ifndef JACKREN_SPLAY
#define JACKREN_SPLAY

#include "include.hpp"

//Splay - BBST
class Splay {
private:
	struct Node {
		int v; //值
		Node* f, * l, * r; //父，左孩子，右孩子
		int cnts; //本子树下包含自身的所有**元素**数目
		int rep; //该值重复了多少次
		Node(int v, Node* f) :v(v), f(f), l(NULL), r(NULL), cnts(1), rep(1) {}
	};
	Node* _root;
#define root _root->r
	void update(Node* p) { //更新cnts值
		p->cnts = p->rep;
		if (p->l)p->cnts += p->l->cnts;
		if (p->r)p->cnts += p->r->cnts;
	}
	bool identify(Node* s, Node* f) { //确定本节点是左孩子还是右孩子，左孩子false，右孩子true
		return !f || s == f->r;
	}
	void connect(Node* s, Node* f, bool r) { //儿子地址,父亲地址,连接到左儿子还是右儿子
		if (f)(r ? f->r : f->l) = s; //父亲更新新儿子
		if (s)s->f = f; //儿子更新新父亲
	}
	void rotate(Node* s) { //儿子节点的旋转
		Node* f = s->f, * gf = s->f->f;
		if (!identify(s, f)) { //左孩子
			connect(s->r, f, false);
			connect(f, s, true);
			connect(s, gf, identify(f, gf));
		}
		else { //右孩子
			connect(s->l, f, true);
			connect(f, s, false);
			connect(s, gf, identify(f, gf));
		}
		update(f);
		update(s);
	}
	void splay(Node* s, Node* e) { //伸展操作，将节点s旋转到节点e所在的位置
		e = e->f;
		while (s->f != e) {
			Node* f = s->f;
			if (f->f == e)rotate(s); //s是e的直系儿子，只需做单旋
			else if (identify(f, f->f) == identify(s, f)) { //Zig-Zig或Zag-Zag，需要先旋父亲节点，再旋儿子节点
				rotate(f);
				rotate(s);
			}
			else { //Zig-Zag或Zag-Zig
				rotate(s);
				rotate(s);
			}
		}
	}

public:
	Splay() {
		_root = new Node(0, NULL);
	}
	~Splay() {
		delete _root;
	}
	Node* find(int v) {
		Node* cur = root;
		if (!cur)return NULL;
		while (1) {
			if (cur->v == v) break;
			Node* next = v < cur->v ? cur->l : cur->r;
			if (!next)break;
			cur = next;
		}
		splay(cur, root);
		root = cur;
		if (cur->v == v)return cur;
		else return NULL;
	}
	void del(int v) {
		Node* cur = find(v);
		if (!cur)return;
		if (cur->rep > 1) { //节点个数出现多于1次
			cur->rep--;
			cur->cnts--;
			return;
		}
		if (!cur->l && !cur->r) { //删除最后一个仅剩的节点
			root = NULL;
		}
		else if (!cur->l) { //无左子树时直接把右子树拼到根
			root = cur->r;
			root->f = _root;
		}
		else { //有左子树时，把左子树的最大值旋到根的左子，将根的右子放到根的左子的右子，删根后补左子树
			Node* l = cur->l;
			while (l->r)l = l->r;
			splay(l, cur->l);
			Node* r = cur->r;
			connect(r, l, true);
			root = l;
			root->f = _root;
			update(l);
		}
		delete cur;
	}
	void insert(int v) {
		Node* cur = find(v);
		if (!root) { //特判空树
			root = new Node(v, _root);
			return;
		}
		if (cur && cur->v == v) { //元素存在，直接把次数+1
			cur->rep++;
			cur->cnts++;
			return;
		}
		Node* newNode = new Node(v, _root);
		if (root->v < v) { //将v接入右侧
			connect(root, newNode, false);
			connect(root->r, newNode, true);
			root->r = NULL;
		}
		else { //将v接入左侧
			connect(root, newNode, true);
			connect(root->l, newNode, false);
			root->l = NULL;
		}
		update(root);
		update(newNode);
		root = newNode;
		newNode->f = _root;
	}
	int rank(int v) {
		Node* cur = find(v);
		if (!cur)return -1;
		int lCnts = cur->l ? cur->l->cnts : 0;
		return lCnts + 1;
	}
	int atrank(int rank) {
		Node* cur = root;
		while (cur) {
			int lCnts = cur->l ? cur->l->cnts : 0;
			if (lCnts < rank && rank <= lCnts + cur->rep) {
				splay(cur, root);
				return cur->v;
			}
			if (rank <= lCnts)cur = cur->l;
			else {
				rank -= lCnts + cur->rep;
				cur = cur->r;
			}
		}
		return -1;
	}
	int upper(int v) {
		Node* cur = find(v);
		int lCnts = root->l ? root->l->cnts : 0;
		if (root->v <= v)return atrank(lCnts + root->rep + 1);
		return root->v;
	}
	int lower(int v) {
		Node* cur = find(v);
		int lCnts = root->l ? root->l->cnts : 0;
		if (root->v >= v)return atrank(lCnts);
		return root->v;
	}
#undef root
};

#endif
