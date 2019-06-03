#include "lz77.h"
#include<string>
#include <math.h>
#include <algorithm>
////////////////////////////////////////////////////////////////////////////////////////////////////7
void LZ77::decode(const vector<Triplet>& encoded_msg, vector<unsigned char>* decoded_msg) {
	string l = "";
	for (int i = 0;i < encoded_msg.size();++i) {
		if (encoded_msg[i].c == 0) {
			decoded_msg->push_back(encoded_msg[i].k);
		}
		else {
			int u = decoded_msg->size() - (int)encoded_msg[i].c;
			for (int z = u;z < u + encoded_msg[i].j;++z) {
				decoded_msg->push_back((*decoded_msg)[z]);
			}
			if (encoded_msg[i].k != 'N')
				decoded_msg->push_back(encoded_msg[i].k);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
//constructor
LZ77::LZ77() {
	s = "";
	fnd = "";
}
///////////////////////////////////////////////////////////////////////////////////////////
//find the substring in the search buffer
//utility func
bool LZ77::find(int rr, int i, int &lstfnd) {
	int match = 0;
	int uu = i - rr + 1 - (fnd.size() - 1);
	for (int k = i;k >= uu;--k) {
		if (k < 0) {
			break;
		}
		if (fnd[fnd.size() - 1] == s[k]) {
			match++;
			lstfnd = k;
			int j = 1;
			for (int y = fnd.size() - 2;y >= 0;--y) {
				if (k - j >= 0 && fnd[y] == s[k - j]) {
					match++;
					lstfnd = k - j;
					j++;
					if ((k - j) < (uu) || (k - j) < 0) {
						break;
					}
				}
				else {
					break;
				}
			}
		}
		if (match == fnd.size()) {
			return 1;
		}
		else {
			match = 0;
		}
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
int LZ77::encode(const vector<unsigned char>& msg, int S, int T, int A, vector<Triplet>* encoded_msg) {
	for (int i = 0;i < msg.size();++i) {
		s += msg[i];
	}
	int lastfind = 0;
	int llfnd = 0;
	for (int i = 0;i < msg.size();++i) {
		fnd += msg[i];
		bool f;
		if (fnd.size() > T) {
			f = false;
		}
		else {
			f = find(S, i - 1, lastfind);
		}
		if (!f) {
			Triplet t;
			t.c = (unsigned char)(i - (fnd.size() - 1) - llfnd);
			t.j = (unsigned char)(fnd.size() - 1);
			t.k = (unsigned char)(fnd[fnd.size() - 1]);
			encoded_msg->push_back(t);
			fnd.clear();
			llfnd = i + 1;
		}
		else {
			llfnd = lastfind;
		}
	}
	if (!fnd.empty()) {
		Triplet t;
		t.c = (unsigned char)s.size() - 1 - (fnd.size() - 1) - llfnd;
		t.j = (unsigned char)fnd.size();
		t.k = (char)'N';
		encoded_msg->push_back(t);
	}
	return encoded_msg->size()*ceil(log2(S) + log2(S + T) + log2(A));
}

