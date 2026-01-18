#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isIdentifier(string s) {
    int state = 0;
    for(int i = 0; i < s.length(); i++) {
        char c = s[i];
        if(state == 0) {
            if(isalpha(c) || c == '_') state = 1;
            else return false;
        }
        else if(state == 1) {
            if(isalnum(c) || c == '_') state = 1;
            else return false;
        }
    }
    return state == 1;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;
    if(isIdentifier(input)) cout << "Valid Identifier" << endl;
    else cout << "Invalid Identifier" << endl;
    return 0;
}
