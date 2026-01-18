#include<bits/stdc++.h>
#include<fstream>
using namespace std;
int main() {
    string file = "C:\\Users\\Maruf\\vs_file\\Compiler_Design\\input.txt"; 
    ifstream input(file);
    ofstream output("C:\\Users\\Maruf\\vs_file\\Compiler_Design\\output.txt");
    if(!input) return 1;
    char ch;
    int charCount = 0, wordCount = 0, lineCount = 0;
    bool inWord = false;
    while (input.get(ch)) {
        ++charCount;
        if (ch == '\n') ++lineCount;
        if ((ch == '\n' || ch == ' ') && inWord) ++wordCount, inWord = false;
        if (ch != '\n' && ch != ' ') inWord = true;
    }
    output << "Total Characters: " << charCount << '\n';
    output << "Total Words: " << wordCount << '\n';
    output << "Total Lines: " << lineCount << '\n';
    return 0;
}