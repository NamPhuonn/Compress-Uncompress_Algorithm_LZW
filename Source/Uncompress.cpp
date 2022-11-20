#pragma one
#include "Uncompress.h"
#include "Compress.h"

void readFile(vector<int>& code, char* nameFile) {
    fstream file;
    file.open(nameFile, ios_base::in | ios_base::binary);

    if (file.fail()){
        cout << "Cannot open file!";
        exit(0);
    }
    else {
        int n;
        while (!file.eof()){
            file >> n;
            code.push_back(n);
        }
    }
    file.close();
}

//Write dencoded data in file .txt
void writeFile(string decode_text, char *nameFile) {
    fstream file;
    file.open(nameFile, ios_base::out);
    if (file.fail()){
        cout << "Cannot open file!";
        exit(0);
    }
    else {
        file << decode_text;
    }
    file.close();
}

//dncode LZW

string decode(map<string, int> &dict, vector<int> code_lzw)
{
    if(code_lzw.size() == 0)
        return "";
    dict.clear(); // xoa noi dung dict neu truoc do da thuc hien mot lenh
    //khoi tao
    map<int, string> table;
    int tableSize, codeSize;
    int k;
    string ch = "";
    string decode_value; // bien de luu lai gia tri cua data sau khi decode
    for (int i = 0; i < 256; i++) { //lay gia tri cua cac ky tu trong bang ACII tu 0 -> 255, day la nhung gia tri ban dau
        ch = "";
        ch += char(i); // su dung ep kieu
        table[i] = ch;
    }

    tableSize = table.size();
    codeSize = code_lzw.size();
    
    string entry = "";
    string res = "";
    int code = 256;
    
    for (int i = 0; i < codeSize; i++) {
        k = code_lzw[i];
        ch = table[k];
        decode_value += table[k];
        if(res != "")
        {
            entry = res + ch[0];
            table[code] = entry;
            dict[entry] = code;
            code++;
        }
        res =  ch;
    }
    return decode_value;
}


void decode_printSize(int inputSize, int outputSize) {
    cout << "Input size: " << inputSize * 10 << " bits\n";
    cout << "Output size: " << outputSize * 8 << " bits\n";
    float k = ((float)(outputSize * 8)/(float)(inputSize * 10) - 1) * 100;
    cout << "Extra space: " << k << "%\n";
}
void uncompressed(int argc, char **argv) {
    
    char *InputPath = argv[2];
    char *OutputPath = argv[3];
    char *OutputInfo = argv[4];

    vector<int> code;
    int inputSize = 0;
    int outputSize = 0;
    readFile(code, InputPath);
    inputSize = code.size();
    map<string, int> dict;
    string data = decode(dict,code);
    writeFile(data, OutputPath);    
    outputSize = data.length();

    if (strcmp(OutputInfo, "-i") == 0) {
        decode_printSize(inputSize,outputSize);
    }
    else if (strcmp(OutputInfo, "-d") == 0) {
        dictionary(dict);
    } 
    else if (strcmp(OutputInfo, "-ind") == 0) {
        decode_printSize(inputSize,outputSize);
        dictionary(dict);
    }
    cout << endl;
}
