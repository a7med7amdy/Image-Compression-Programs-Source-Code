// includes here
#include <map>
#include<iostream>
#include <fstream>
#include <string>
#include<vector>
#include<math.h>
#include "lz77.h"
using  namespace std;

int main(int argc, char* argv[])
{
	cout << endl<<endl<<endl;
	vector<unsigned char> v;
	vector<Triplet> enc;
	string mode = argv[1];
	string kind;
	int size = 1;
	string word;
	int nocols;
	if (mode == "-encode") {
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
	}
	else {
		string word;
		string h;
		int p = 0;
		Triplet t;
		int k = 0;
		while (cin >> word) {
			switch (p)
			{
			case 0:
				break;
			default:
				if (k == 0) {
					t.c = stoi(word);
					k++;
				}
				else if (k == 1) {
					t.j = stoi(word);
					k++;
				}
				else if (k == 2) {
					if (word[0] != 'N')
						t.k = stoi(word);
					else
						t.k = 'N';
					enc.push_back(t);
					k = 0;
				}
				break;
			}
			p++;
		}
	}
	LZ77 *f = new LZ77();
	vector<Triplet>encoded_msg;
	if (mode == "-encode" && argc == 5)
	{
		//the encoding alpha
		ofstream myfile("image.enc");
		if (myfile.is_open())
		{
			//  "if there's N in the output then it's (300) indicates that the last indexes are already found in the dictionary" 
			int eee = f->encode(v, stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), &encoded_msg);
			cout << "if there's N in the output indicates to ( NULL ) shows that the last indexes are already found in the dictionary" << endl;
			cout << "the no. of bits = " << eee << endl;
			cout << "compression ratio = " << (double)(v.size()*8) / double(eee)<<endl;
			myfile << eee << endl;
			for (int i = 0;i < encoded_msg.size();++i) {
				if (encoded_msg[i].k != 'N') {
					myfile << (int)(encoded_msg[i].c) << " " << (int)(encoded_msg[i].j) << " " << (int)(encoded_msg[i].k) << endl;
				}
				else {
					myfile << (int)encoded_msg[i].c << " " << (int)encoded_msg[i].j << " " << (char)encoded_msg[i].k << endl;
				}
			}
			myfile.close();
		}
		else cout << "Unable to open file";
	}
	else if (mode == "-decode")
	{
		//out in the file
		vector<unsigned char>vvv;
		f->decode(enc, &vvv);
		ofstream myfile("lz77.txt");
		if (myfile.is_open())
		{
			myfile << "P2" << endl;
			myfile << argv[2] << " " << argv[3] << endl;
			myfile << argv[4] << endl;
			int z = 1;
			for (int i = 0;i < vvv.size();++i) {
				if (vvv[i] != 'N') {
					myfile << (int)vvv[i] << " ";
					z++;
				}
				if (z > stoi(argv[2])) {
					myfile << endl;
					z = 1;
				}
			}
			myfile.close();
		}
		else cout << "Unable to open file";
		///////////////////////////
	}
	else if (mode == "-encode" && argc > 5)
	{
		// to make the correlation
		int y = 0;
		int prev;
		int giv;
		//calc the diff between the pixels first
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
		ofstream myfile("image.enc");
		if (myfile.is_open())
		{
			// << "if there's N in the output then it's (300) indicates that the last indexes are already found in the dictionary" << endl;
			int eee = f->encode(v, stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), &encoded_msg);
			cout << "total no of bits = " << eee << endl;
			cout << "compression ratio = " << (double)(v.size() * 8) / double(eee) << endl;
			myfile << eee << endl;
			for (int i = 0;i < encoded_msg.size();++i) {
				if (encoded_msg[i].k != 'N') {
					myfile << (int)(encoded_msg[i].c) << " " << (int)(encoded_msg[i].j) << " " << (int)(encoded_msg[i].k) << endl;
				}
				else {
					myfile << (int)encoded_msg[i].c << " " << (int)encoded_msg[i].j << " " << (char)encoded_msg[i].k << endl;
				}
			}
			myfile.close();
		}
		else cout << "Unable to open file";
	}
}