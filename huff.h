#pragma once

#include<iostream>
#include<fstream>

#include<vector>
#include<queue>
//#include<algorithm>
using namespace std;


class dicNode {
public:
	char character;
	int weight;
	char* code;
	dicNode() :character(0), weight(0), code(NULL) {}
	dicNode(char t) :character(t), code(NULL), weight(0) {}
	dicNode(char t, int w) :character(t), weight(w), code(NULL) {}
};
void dicSortDown(dicNode* dic, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size - 1; j > 0; j--) {
			if (dic[j].weight > dic[j - 1].weight) {
				char t = dic[j].character;
				dic[j].character = dic[j - 1].character;
				dic[j - 1].character = t;
				int w = dic[j].weight;
				dic[j].weight = dic[j - 1].weight;
				dic[j - 1].weight = w;
			}
		}
	}
}




class treenode {
public:
	treenode* l = NULL;
	treenode* r = NULL;
	int weight = 0;
	dicNode *dicN = NULL;
};
class tree {
public:
	tree() {
		root = NULL;
	}
	~tree() {
	}
	treenode* root;
	bool operator <(const tree& b) const {
		return this->root->weight < b.root->weight;
	}
	bool operator >(const tree& b) const {
		return this->root->weight > b.root->weight;
	}
	bool operator ==(const tree& b) const {
		return this->root->weight == b.root->weight;
	}
};
void erg(treenode* node) {
//������֤
	static char co[10] = { 0 };
	static int len = 0;
	if (node->l == NULL && node->r == NULL && node->dicN != NULL) {
		node->dicN->code = new char[len + 1];
		for (int i = 0; i < len; i++) {
			node->dicN->code[i] = co[i];
		}
		node->dicN->code[len] = '\0';
		len--;
		return;
	}
	if (node->l != NULL) {
		co[len] = '0';
		len++;
		erg(node->l);
	}
	if (node->r != NULL) {
		co[len] = '1';
		len++;
		erg(node->r);
	}
	len--;
}
class Huffman {

public:
	dicNode* dic;
	int dicSize;

	Huffman(char* filename) {
		//�������ļ��� ͳ�ƴ�Ƶ �����ֵ�
		dic = new dicNode[256];
		dicSize = 0;
		ifstream fin;
		fin.open(filename);
		//�����ı� ͳ���ַ��������������ֵ� ͳ���ַ�Ƶ��
		while (!fin.eof()) {
			char t = 0;
			int i = 0;			fin >> t;
			while (dic[i].character != t && i < dicSize) i++;
			if (i == dicSize) {
				dic[i].character = t;
				dic[i].weight = 1;
				dicSize++;
			}
			else {
				dic[i].weight++;
			}
		}
		dicSortDown(dic, dicSize);//Ƶ�ʴ�ķ���ǰ����߲����ٶ�

		//ÿ���ַ�����һ�����ڵ㣬��ȫ��Ѻ����С��

		priority_queue<tree, vector<tree>, greater<tree>> heap;
		for (int i = 0; i < dicSize; i++) {
			tree* t = new tree;
			t->root = new treenode;
			t->root->weight = dic[i].weight;
			t->root->dicN = dic + i;
			heap.push(*t);
		}
		while (heap.size() > 1) {
			//cout << heap.size() << ' ';
			treenode* a = heap.top().root;
			//cout << a->weight << ' ';
			heap.pop();
			treenode* b = heap.top().root;
			//cout << b->weight<<endl;
			heap.pop();
			//cout << heap.size() << ' ';
			tree* t = new tree;
			t->root = new treenode;
			t->root->l = a;
			t->root->r = b;
			t->root->weight = a->weight + b->weight;
			heap.push(*t);
			//cout << heap.size() << ' '<<endl;
		}
		erg(heap.top().root);


		for (int i = 0; i < dicSize; i++) {
			cout << dic[i].character << ' ' << dic[i].weight << ' ' << dic[i].code << endl;
		}
		//д���������ļ���
		//��ʵ��

		cout << "���������뽨�����";

	}


	void zip(char* inputfile, char* outputfile) {
		ifstream fin;
		fin.open(inputfile);
		ofstream fout;
		fout.open(outputfile);
		char t = 0;
		fin >> t;
		while (!fin.eof()) {

			for (int i = 0; i < dicSize; i++) {
				if (t == dic[i].character) {
					fout << dic[i].code;
				}

			}
			fin >> t;
		}
	}
	void unzip(char* inputfile, char* outputfile) {
		ifstream fin;
		fin.open(inputfile);
		ofstream fout;
		fout.open(outputfile);
		int maxcodelen = strlen(dic[dicSize - 1].code);
		char* t = new char[maxcodelen + 1];
		for (int i = 1; i <= maxcodelen && !fin.eof(); i++) {//��һ����������
			fin >> t[i - 1];
			for (int j = 0; j < dicSize; j++) {//���ֵ�
				if (i != strlen(dic[j].code))
					continue;
				bool par = true;
				for (int k = 0; k < i; k++) {//����ÿ���ֵ�ele�˶�
					if (dic[j].code[k] != t[k]) {
						par = false;
						break;
					}
				}
				if (par == true) {
					fout << dic[j].character;
					//���t
					i = 0;
				}
			}
		}

	}
};


