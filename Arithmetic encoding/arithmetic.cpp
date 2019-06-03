#include "arithmetic.h"
#include <map>
#include <algorithm>
#include<math.h>
#include <iostream>
using namespace std;
//i consider the bitset of fraction is the bitset of the decimal after point as the i don't know how '.' will be encoded
//the first number is 0, other wise it'll be 0.99999.... so it will indicate (1)
//if 0.000000 so it's 0
double Arithmetic::binary_to_decimal(const bitset<32>& fraction) {
	//the fraction value;
	double x = 0;
	//the decrementer
	int y = -1;
	for (int i = 0;i < 32;++i) {
		x = x + fraction[i] * pow(2, y);
		y--;
	}
	return x;
}
///////////////////////////////////////////////////////
bitset<32> Arithmetic::decimal_to_binary(double fraction) {
	int x = 0;
	bitset<32>fract;
	while (x < 32)
	{
		// Find next bit in fraction 
		fraction *= 2;
		int fr = fraction;

		if (fr == 1)
		{
			fract[x] = fr;
			fraction -= fr;
		}
		else {
			fract[x] = 0;
		}
		x++;
	}

	return fract;
}
///////////////////////////////////////////////////////
int Arithmetic::encode(const vector<unsigned char>& msg, int num_symbols_per_block, vector<bitset<32> >* encoded_msg) {
	//a7seb prob el el msg
	//we 23mel recursion 3la keda
	map<unsigned char, int>mp;
	for (int i = 0;i < msg.size();++i) {
		mp[msg[i]]++;
	}
	vec.resize(mp.size());
	map<unsigned char, int>::iterator it = mp.begin();
	int k = 0;
	//calculting the prob. of each symbol
	for (;it != mp.end();++it) {
		vec[k].first.first = -1;
		vec[k].first.second = (double(it->second) / double(msg.size()));
		vec[k].second = it->first;
		k++;
	}
	//sorting the symbols
	sort(vec.begin(), vec.end());
	for (int i = 0;i < vec.size();++i) {
		if (i == 0) {
			vec[i].first.first = 0;
		}
		else {
			vec[i].first.first = vec[i - 1].first.second;
			vec[i].first.second = vec[i].first.first + vec[i].first.second;
		}
	}
	//take every block symbol

	//encode the msg by taking each no of symbols together
	double l = 0, u = 0;
	int total = 0;
	bool first = 1;
	for (int i = 0;i < msg.size();i += num_symbols_per_block) {
		for (int j = i;j < i + num_symbols_per_block;++j) {
			if (j < msg.size()) {
				for (int k = 0;k < vec.size();++k) {
					if (vec[k].second == msg[j]) {
						if (first) {
							l = vec[k].first.first;
							u = vec[k].first.second;
							first = 0;
						}
						else {
							double f = l;
							l = f + (u - f)*vec[k].first.first;
							u = f + (u - f)*vec[k].first.second;
						}
						break;
					}
				}
			}
		}
		double tag = (l + u) / 2;
		encoded_msg->push_back(decimal_to_binary(tag));
		first = 1;
		total += ceil(log2(1 / (u - l))) + 1;
	}
	return total;
}
///////////////////////////////////////////////////////////
void Arithmetic::decode(const vector<bitset<32> >& encoded_msg, int num_symbols_per_block, vector<unsigned char>* decoded_msg) {
	for (int i = 0;i < encoded_msg.size();++i) {
		double t = binary_to_decimal(encoded_msg[i]);
		double l = 0, u = 1;
		double fff;
		for (int k = 0;k < num_symbols_per_block;++k) {
			fff = (t - l) / (u - l);
			for (int z = 0;z < vec.size();++z) {
				if (vec[z].first.first <= fff && vec[z].first.second >= fff) {
					decoded_msg->push_back(vec[z].second);
					double f = l;
					l = f + (u - f)*vec[z].first.first;
					u = f + (u - f)*vec[z].first.second;
					break;
				}
			}
		}
	}
}
/////////////////////////////////////////////////////////
vector<pair<pair<double, double>, unsigned char>>* Arithmetic::getvec() {
	return &vec;
}
///////////////////////////////////////////////////////////
void Arithmetic::setvec(vector<pair<pair<double, double>, unsigned char>> &y) {
	vec.resize(y.size());
	for (int i = 0;i < y.size();++i) {
		vec[i] = y[i];
	}
}
//////////////////////////////////////////////////////////////
