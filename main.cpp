#include<iostream>
#include<fstream>
#include"huff.h"
using namespace std;
int main() {
	char orgfilename[] = "orgfile.txt";
	char charfile[] = "charfile.txt";
	char codefile[] = "codefile.txt";
	char out1[] = "out1.txt";
	char out2[] = "out2.txt";
	Huffman huffman(orgfilename);
	huffman.zip(charfile, out1);
	huffman.unzip(codefile, out2);
}