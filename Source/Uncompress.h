#pragma one
#include"Header.h"

#ifndef UNCOMPRESS_H
#define UNCOMPRESS_H

void readFile(vector<int>& code, char* nameFile);
void writeFile(string decode_text, char *nameFile);
string decode(map<string, int> &dict, vector<int> code_lzw);
void printSize(int inputSize, int outputSize);
void uncompressed(int argc, char **argv);

#endif