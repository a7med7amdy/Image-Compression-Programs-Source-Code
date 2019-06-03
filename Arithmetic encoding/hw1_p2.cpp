#include <iostream>
#include "arithmetic.h"
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
using  namespace std;

int main(int argc, char* argv[])
{
	////////////////////////////////////////////////
	vector<unsigned char> v;
	string mode = argv[1];
	string kind;
	int size = 1;
	string word;
	int nocols;
	Arithmetic a = Arithmetic();
	/////////////////////////////////////////////////
	if (mode == "-decode") {
		vector<bitset<32>>vv;
		//to take meta data in it
		vector<pair<pair<double, double>, unsigned char>>metadata;
		string y = "";
		int p = 1;
		int q = stoi(argv[4]);
		int ooo = stoi(argv[4]);
		int counter = 1;
		int mdc = 0;
		double in1, in2;
		unsigned int in3;
		pair<pair<double, double>, unsigned char>pp1;
		pair<double, double>pp2;
		while (cin >> word) {
			//taking meta data
			if (counter > ceil((double(stoi(argv[3])*stoi(argv[4])) / double(stoi(argv[2]))))) {
				if (mdc == 0) {
					in1 = stod(word);
					mdc++;
				}
				else if (mdc == 1) {
					in2 = stod(word);
					mdc++;
				}
				else {
					in3 = stoi(word);
					mdc = 0;
					pp2 = make_pair(in1, in2);
					pp1 = make_pair(pp2, in3);
					metadata.push_back(pp1);
				}
			}
			else {
				y += word;
				p++;
				if (p > 32) {
					counter++;
					bitset<32>b(y);
					vv.push_back(b);
					p = 1;
					y = "";
				}
			}
		}
		vector<unsigned char>vvvv;
		a.setvec(metadata);
		a.decode(vv, stoi(argv[2]), &vvvv);
		ofstream myfile("arithmetic.txt");
		if (myfile.is_open())
		{
			//decode the file
			myfile << "P2" << endl;
			myfile << argv[3] << " " << argv[4] << endl;
			myfile << argv[5] << endl;
			int z = 1;
			for (int i = 0;i < vvvv.size();++i) {
				myfile << (int)vvvv[i] << " ";
				z++;
				if (z > stoi(argv[3])) {
					myfile << endl;
					z = 1;
				}
			}
			myfile.close();
		}
		else {
			cout << "Unable to open file";
		}
	}
	else if (mode == "-encode") {
		string word;
		string h;
		int p = 0;
		int k = 0;
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
		vector<bitset<32>>vec;
		int nn = a.encode(v, stoi(argv[2]), &vec);
		cout << "the code:-" << "                      " << "the tags:-" << endl;
		for (int i = 0;i < vec.size();++i) {
			cout << vec[i] << " ";
			cout << a.binary_to_decimal(vec[i]) << " " << endl;
		}
		double cr = double(v.size() * 8) / double(nn);
		cout << "the compression ratio is " << cr << endl;
		cout << "total no of bits are : " << nn << endl;
		cout << endl;
		ofstream myfile("image.enc");
		if (myfile.is_open())
		{
			for (int k = 0;k < vec.size();++k) {
				for (int z = 31;z >= 0;--z) {
					myfile << vec[k][z] << " ";
				}
				myfile << endl;
			}
			/////////////////////////////////////////////////////////////////
			//out the lower ,the upper, the char
			vector<pair<pair<double, double>, unsigned char>>*metadata;
			metadata = a.getvec();
			for (int i = 0;i < metadata->size();++i) {
				myfile << (*metadata)[i].first.first << " " << (*metadata)[i].first.second << " " << (int)(*metadata)[i].second;
				myfile << endl;
			}
			/////////////////////////////////////////////////////////////////
			myfile.close();
		}
		else {
			cout << "Unable to open file" << endl;
		}
	}
	else if (mode == "-bin_to_dec") {
		//change from hex format to bin format
		string s = argv[2];
		stringstream ss;
		ss << hex << s;
		unsigned bin;
		ss >> bin;
		bitset<32> b(bin);
		bitset<32> bb;
		for (int i = 0;i < 32;++i) {
			bb[i] = b[31 - i];
		}
		cout << "the decimal value is " << a.binary_to_decimal(bb) << endl;
	}
	else {
		bitset<32>bt;
		bt = a.decimal_to_binary(stod(argv[2]));
		cout << "the decimal value is " << endl;
		cout << "0.";
		for (int i = 0;i < 32;++i) {
			cout << bt[i];
		}
		cout << endl;
	}
	system("pause");
	return 0;
}