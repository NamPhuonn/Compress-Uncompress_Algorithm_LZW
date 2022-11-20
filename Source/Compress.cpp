#include "Compress.h"

//Read file .txt
void readFile(string &data, char* nameFile, int &size) {
    fstream file;
    file.open(nameFile, ios_base::in);

    if (file.fail()){
        cout << "Cannot open file!";
        exit(0);
    }
    else {
        string s;
        while (!file.eof()){
            file >> s;
            data += s;
        }

        //Move the position to the end of file
        file.seekg(0, ios::end);

        //Get size of file
        size = file.tellg();
    }
    file.close();
}

//Write encoded data in file .lzw
void writeFile(vector<int> list, char *nameFile, int &size) {
    fstream file;
    file.open(nameFile, ios_base::out | ios_base::binary);
    if (file.fail()){
        cout << "Cannot open file!";
        exit(0);
    }
    else {
        for (int i = 0; i < list.size(); i++){
            if(i == list.size() - 1)
                file << list[i];
            else file << list[i] << " ";
        }

        //Get size of file
        size = list.size();
    }
    file.close();
}

//Encode LZW
vector<int> encode(map<string, int> &dict, string character){
    //Create string table as ASCII code
    map<string, int> table;
	int tableSize = 256;
	for(int i = 0; i < tableSize; ++i)
		table[string(1,i)] = i;

    int dictSize = 256;
	vector<int> res;
	string p;
	for(char c : character){
        //Check p + c is in the string table
		if(table.count(p + c)){
            p += c;
        }
		else{
            //Add p + c at the end of string table
			res.emplace_back(table[p]);
			table[p + c] = tableSize++;
            dict[p + c] = dictSize++;
			p = c;
		}
	}
    //Add last string
	if(p.size()) 
        res.emplace_back(table[p]);
	return res;
}

//Compare two pair
bool cmp(pair<string, int>& a, pair<string, int>& b)
{
    return a.second < b.second;
}

//Dictionary LZW when compress  
void dictionary(map<string, int>& M)
{
    vector<pair<string, int> > A;
  
    // Copy key-value pair from Map to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);
  
    for (auto& it : A) {
        cout << it.first << ": " << it.second << endl;
    }
}

void printSize(int inputSize, int outputSize) {
    cout << "Input size: " << inputSize * 8 << " bits\n";
    cout << "Output size: " << outputSize * 10 << " bits\n";
    float k = (1 - (float)(outputSize * 10)/(float)(inputSize * 8)) * 100;
    cout << "Space saved: " << k << "%\n";
}
void compressed(int argc, char **argv) {
    
    char *InputPath = argv[2];
    char *OutputPath = argv[3];
    char *OutputInfo = argv[4];

    string data = "";
    int inputSize = 0;
    int outputSize = 0;
    readFile(data, InputPath, inputSize);
    map<string, int> dict;
    vector<int> dataEncoded = encode(dict,data);
    writeFile(dataEncoded, OutputPath, outputSize);

    if (strcmp(OutputInfo, "-i") == 0) {
        printSize(inputSize,outputSize);
    }
    else if (strcmp(OutputInfo, "-d") == 0) {
        dictionary(dict);
    } 
    else if (strcmp(OutputInfo, "-ind") == 0) {
        printSize(inputSize,outputSize);
        dictionary(dict);
    }
    
}