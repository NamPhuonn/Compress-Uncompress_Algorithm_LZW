#pragma one
#include "Header.h"


#ifndef COMPRESS_H
#define COMPRESS_H

void readFile(string &data, char* nameFile, int &size);
void writeFile(vector<int> list, char *nameFile);
vector<int> encode(map<string, int> &dict, string character);
bool cmp(pair<string, int>& a,pair<string, int>& b);
void dictionary(map<string, int>& M);
void printSize(int inputSize, int outputSize);
void compressed(int argc, char **argv);

#endif