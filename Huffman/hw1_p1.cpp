#include <map>
#include<iostream>
#include <fstream>
#include <fstream>
#include <string>
#include<vector>
#include<math.h>
#include "huffman.h"
using  namespace std;


int main(int argc, char* argv[])
{
	vector<unsigned char> v;

	string mode = argv[1];
	string kind;
	int size = 1;
	string word;
	int nocols;
	int p = 0;
	while (cin >> word) {
		switch (p)
		{
		case 0:
			kind = word;
			break;
		case 1:
			size *= stoi(word);
			break;
		case 2:
			size *= stoi(word);
			nocols = stoi(word);
			break;
		case 3:
			break;
		default:
			v.push_back(stoi(word));
			break;
		}
		p++;
	}
	Huffman *f = new Huffman();
	if (mode == "-entropy")
	{
		vector<Symbol> prob(size);
		cout << "The entropy value is  " << f->compute_entropy(v, &prob) << endl;
	}
	else if (mode == "-tree")
	{
		vector<Symbol> prob(size);
		f->compute_entropy(v, &prob);
		f->build_tree(prob);
		f->print_code_table();
	}
	if (argc == 2 && mode == "-encode")
	{
		vector<Symbol> prob(size);
		f->compute_entropy(v, &prob);
		f->build_tree(prob);
		vector<unsigned int> encoded_msg;
		int u = f->encode(v, &encoded_msg);
		cout << "encoded message is:  " << endl;
		int ww = 1;
		for (int i = 0;i < encoded_msg.size();++i) {
			cout << encoded_msg[i] << " ";
			ww++;
			if (ww > nocols) {
				cout << endl;
				ww = 1;
			}
		}
		cout << endl;
		cout << "total no of bits = " << u << endl;
		cout << "compression ratio is = " << (8.0*double(size)) / double(u) << endl;
	}
	else if (mode == "-encode"&&argc == 3)
	{
		//computing the decorrelation,
		int y = 0;
		int prev;
		int giv;
		for (int i = 0;i < v.size();++i) {
			if (i < nocols + y) {
				if (i - y != 0) {
					int giv = (int)v[i];
					v[i] = abs((int)v[i] - prev);
					prev = giv;
				}
				else {
					prev = v[i];
				}
			}
			else {
				y = i;
				prev = v[i];
			}
		}
		vector<Symbol> prob(size);
		cout << f->compute_entropy(v, &prob) << endl;
		f->build_tree(prob);
		f->print_code_table();
		vector<unsigned int> encoded_msg;
		int u = f->encode(v, &encoded_msg);
		int ww = 1;
		cout << "encoded message is : " << endl;
		for (int i = 0;i < encoded_msg.size();++i) {
			cout << encoded_msg[i] << "  ";
			ww++;
			if (ww > nocols) {
				cout << endl;
				ww = 1;
			}
		}
		cout << endl;
		cout << "total no of bits = " << u << endl;
		cout << "compression ratio is = " << (8.0*double(size)) / double(u) << endl;
	}
}
/*int main() {
	Huffman f = Huffman();
	vector<Symbol> prob(10);
	vector<unsigned char>v(10);
	v[0] = 50;
	v[1] = 50;
	v[2] = 100;
	v[3] = 50;
	v[4]= 150;
	v[5]= 150;
	v[6] = 50;
	v[7] = 150;
	v[8] = 200;
	v[9] = 250;
	int y = 0;
	int prev;
	int giv;
	for (int i = 0;i < v.size();++i) {
		if (i < 3 + y) {
			if (i - y != 0) {
				int giv = (int)v[i];
				v[i] = abs((int)v[i] - prev);
				prev = giv;
			}
			else {
				prev = v[i];
			}
		}
		else {
			y = i;
			prev = v[i];
		}
	}
	f.compute_entropy(v, &prob);
	f.build_tree(prob);
	f.print_code_table();
	system("pause");
}*/

