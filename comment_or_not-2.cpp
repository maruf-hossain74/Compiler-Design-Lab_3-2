#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

string trimLeading(const string &s){
    size_t i = 0;
    while(i < s.size() && isspace(static_cast<unsigned char>(s[i]))) ++i;
    return s.substr(i);
}

int main(){
    string filename = "input.txt";
    // cin >> filename;
    ifstream file(filename);
    if(!file) return 1;
    string line;
    int lineNumber = 1;
    while(getline(file, line)){
        string t = trimLeading(line);
        if(t.rfind("//", 0) == 0) cout << "Line " << lineNumber << ": Comment (single-line)\n";
        else if(t.rfind("/*", 0) == 0) cout << "Line " << lineNumber << ": Comment (multi-line start or single-line block)\n";
        else if(t.find("*/") != string::npos) cout << "Line " << lineNumber << ": Comment (multi-line end)\n";
        else cout << "Line " << lineNumber << ": Not a comment\n";
        ++lineNumber;
    }
    return 0;
}