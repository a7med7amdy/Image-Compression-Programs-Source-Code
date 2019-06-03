#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
// Define the tree node struct here ...

// Define a symbol struct here to hold the symbol (grayscale value)
// and its probability/frequency
struct Symbol {
	// Grayscale value of the symbol
	double prob;
	unsigned char val;
	string code;
	// ...
	//creating a symbol
	void createsympol(char s, double p) {
		prob = p;
		val = s;
	}
};

struct Node {
	// ...
	Symbol s;
	Node*leftchild;
	Node*rightchild;
	Node(char ss, double p) {
		s.createsympol(ss, p);
		leftchild = NULL;
		rightchild = NULL;
	}
};

class Huffman {
private:
	// Data members here ... for example to store the tree and the codeword 
	// hash table
	//mp to calc the no of bits needed after encoding
	map<unsigned char, int>calc_total_bits;
	Node* tree;
	//carring the encoded new char
	map<unsigned char, int>mp1;
	// ...
	//utilities (recursive)functions
	//delete tree
	void del(Node*, Node*, int);
	//void encoding(Node*, string,int&);
	void encoding(Node*, string);
	//print code
	void printcode(Node*, string);
	//encode the message
	//void encodemess(const vector<unsigned char>&msg,vector<unsigned int>*&encoded,Node*n,int i);
public:
	// Constructor and destructor
	Huffman();

	~Huffman();
	//set the left child
	void set_lc(Node*n);
	//set the right child
	void set_rc(Node*n);


	// A function to compute the entropy of the input message and
	// stores the probabilities of the different symbols in
	// the input array.
	float compute_entropy(const vector<unsigned char>& msg,
		vector<Symbol>* prob);

	// A function to build the Huffman tree given the computed
	// symbol probabilities.
	void build_tree(const vector<Symbol>& prob);

	// A function to print the code table computed from the build_tree above.
	void print_code_table();

	// A function to encode the input message using the computed tree 
	// and store the output in the output array, where each entry
	// corresponds to the codeword for an input symbol in the message.
	//
	// The function should return the number of bits in the encoded 
	// message.
	int encode(const vector<unsigned char>& msg,
		vector<unsigned int>* encoded_msg);


};
