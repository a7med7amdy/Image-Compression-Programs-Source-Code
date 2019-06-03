#include "huffman.h"
#include <algorithm>
#include <map>
#include <queue>
#include <functional>
#include <math.h>
//////////////////////////////////////////
//Constructor
Huffman::Huffman() {
	tree = NULL;
	for (int i = 0;i < 256;++i) {
		mp1[i] = 0;
	}
}
//////////////////////////////////
float Huffman::compute_entropy(const vector<unsigned char>& msg, vector<Symbol>* prob) {
	map<char, int>mp;
	for (int i = 0;i < msg.size();++i) {
		mp[msg[i]]++;
	}
	map<char, int>::iterator it = mp.begin();
	int k = 0;
	for (;it != mp.end();++it) {
		(*prob)[k].val = it->first;
		//(*prob)[k].prob = (double(it->second)/double(msg.size()),2)*10./100.;
		(*prob)[k].prob = (double(it->second) / double(msg.size()));
		k++;
	}
	prob->resize(mp.size());
	double intropy = 0;
	for (int i = 0;i < prob->size();++i) {
		intropy -= (*prob)[i].prob*log2((*prob)[i].prob);
	}
	return intropy;
}
////////////////////////////////////////////////////////////////////////////////////
void Huffman::build_tree(const vector<Symbol>& prob) {
	//vector of pairs of prob and nodes in order to sort about prob first ascendingly
	vector<pair<double, Node*>>tr;
	for (int i = 0;i < prob.size();++i) {
		Node*n = new Node(prob[i].val, prob[i].prob);
		tr.push_back(make_pair(prob[i].prob, n));
	}
	sort(tr.begin(), tr.end());
	int N = tr.size();
	while (N > 1) {
		Node*n = new Node(tr[0].second->s.val + tr[1].second->s.val, tr[0].second->s.prob + tr[1].second->s.prob);
		n->leftchild = tr[0].second;
		n->rightchild = tr[1].second;
		tr.push_back(make_pair(n->s.prob, n));
		//give the taken one high prob in order to be at last after sorting 
		//to indicate that it's taken
		tr[0].first = 10000000;
		tr[1].first = 10000000;
		sort(tr.begin(), tr.end());
		N = N - 1;
	}
	tree = tr[0].second;
}
//////////////////////////////////////////////////////////////////////////////////////////
//print the code of each symbol and store its code after calculation
void Huffman::printcode(Node*n, string s) {
	if (n->leftchild == NULL && n->rightchild == NULL) {
		cout << "symbol= " << (int)n->s.val << ", code= " << s << endl;
		n->s.code = s;
		s.pop_back();
		return;
	}
	printcode(n->leftchild, s + "0");
	printcode(n->rightchild, s + "1");
}
//////////////////////////////////////////////////////////////////////////////////////////////
void Huffman::print_code_table() {
	printcode(tree, "");
}
//////////////////////////////////////////////////////////////////////////////////////////////
int Huffman::encode(const vector<unsigned char>& msg, vector<unsigned int>* encoded_msg) {
	int ret = 0; //the total no needed
	encoding(tree, "");
	for (int i = 0;i < msg.size();++i) {
		ret += calc_total_bits[msg[i]];
		encoded_msg->push_back(mp1[msg[i]]);
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////////////////////////////
Huffman::~Huffman() {
	del(tree, tree, -1);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Huffman::del(Node*n, Node*p, int x) {
	if (n->leftchild == NULL && n->rightchild == NULL) {
		if (x == 1) {
			delete p->rightchild;
			p->rightchild = NULL;
		}
		else {
			delete p->leftchild;
			p->leftchild = NULL;
		}
		return;
	}
	del(n->leftchild, n, 0);
	del(n->rightchild, n, 1);
}
/////////////////////////////////////////////////////////////////////////////////////////////
//utility helping function
void Huffman::encoding(Node*n, string s) {
	if (n->leftchild == NULL && n->rightchild == NULL) {
		n->s.code = s;
		calc_total_bits[n->s.val] = s.size();
		mp1[n->s.val] = stoi(s, nullptr, 2);
		s.pop_back();
		return;
	}
	encoding(n->leftchild, s + "0");
	encoding(n->rightchild, s + "1");
}
///////////////////////////////////////////////////////////////////



