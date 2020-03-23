#ifndef JACKREN_SPLAY
#define JACKREN_SPLAY

#include "include.hpp"

//Splay - BBST
class Splay {
private:
	struct Node {
		int v; //ֵ
		Node* f, * l, * r; //�������ӣ��Һ���
		int cnts; //�������°������������**Ԫ��**��Ŀ
		int rep; //��ֵ�ظ��˶��ٴ�
		Node(int v, Node* f) :v(v), f(f), l(NULL), r(NULL), cnts(1), rep(1) {}
	};
	Node* _root;
#define root _root->r
	void update(Node* p) { //����cntsֵ
		p->cnts = p->rep;
		if (p->l)p->cnts += p->l->cnts;
		if (p->r)p->cnts += p->r->cnts;
	}
	bool identify(Node* s, Node* f) { //ȷ�����ڵ������ӻ����Һ��ӣ�����false���Һ���true
		return !f || s == f->r;
	}
	void connect(Node* s, Node* f, bool r) { //���ӵ�ַ,���׵�ַ,���ӵ�����ӻ����Ҷ���
		if (f)(r ? f->r : f->l) = s; //���׸����¶���
		if (s)s->f = f; //���Ӹ����¸���
	}
	void rotate(Node* s) { //���ӽڵ����ת
		Node* f = s->f, * gf = s->f->f;
		if (!identify(s, f)) { //����
			connect(s->r, f, false);
			connect(f, s, true);
			connect(s, gf, identify(f, gf));
		}
		else { //�Һ���
			connect(s->l, f, true);
			connect(f, s, false);
			connect(s, gf, identify(f, gf));
		}
		update(f);
		update(s);
	}
	void splay(Node* s, Node* e) { //��չ���������ڵ�s��ת���ڵ�e���ڵ�λ��
		e = e->f;
		while (s->f != e) {
			Node* f = s->f;
			if (f->f == e)rotate(s); //s��e��ֱϵ���ӣ�ֻ��������
			else if (identify(f, f->f) == identify(s, f)) { //Zig-Zig��Zag-Zag����Ҫ�������׽ڵ㣬�������ӽڵ�
				rotate(f);
				rotate(s);
			}
			else { //Zig-Zag��Zag-Zig
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
		if (cur->rep > 1) { //�ڵ�������ֶ���1��
			cur->rep--;
			cur->cnts--;
			return;
		}
		if (!cur->l && !cur->r) { //ɾ�����һ����ʣ�Ľڵ�
			root = NULL;
		}
		else if (!cur->l) { //��������ʱֱ�Ӱ�������ƴ����
			root = cur->r;
			root->f = _root;
		}
		else { //��������ʱ���������������ֵ�����������ӣ����������ӷŵ��������ӵ����ӣ�ɾ����������
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
		if (!root) { //���п���
			root = new Node(v, _root);
			return;
		}
		if (cur && cur->v == v) { //Ԫ�ش��ڣ�ֱ�ӰѴ���+1
			cur->rep++;
			cur->cnts++;
			return;
		}
		Node* newNode = new Node(v, _root);
		if (root->v < v) { //��v�����Ҳ�
			connect(root, newNode, false);
			connect(root->r, newNode, true);
			root->r = NULL;
		}
		else { //��v�������
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
