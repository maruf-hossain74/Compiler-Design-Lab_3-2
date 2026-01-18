#include <iostream>
#include <cctype>
#include <string>
using namespace std;

bool isValidIdentifier(const string &s){

    // keyword doesn't checked
    if(s.empty() || (!isalpha(s[0]) && s[0] != '_')) return false;
    for(char c : s) if(!isalnum(c) && c != '_') return false;
    return true;
}

int main(){
        string id;
        cin >> id;
        if(isValidIdentifier(id)) cout << "Valid Identifier\n";
        else cout << "Invalid Identifier\n";
    return 0;
}