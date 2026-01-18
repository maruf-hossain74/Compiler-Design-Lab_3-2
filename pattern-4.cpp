#include <iostream>
#include <string>
using namespace std;

bool is_a(const string &s){
    return s == "a";
}

bool is_a_star_b_plus(const string &s){
    int i = 0, n = s.size();
    while(i < n && s[i] == 'a') i++;
    int b = 0;
    while(i < n && s[i] == 'b'){ i++; b++; }
    return i == n && b > 0;
}

bool is_abb(const string &s){
    return s == "abb";
}

int main(){
    string s;
    cin >> s;
    if(is_a(s)) cout << "String is under 'a'\n";
    else if(is_a_star_b_plus(s)) cout << "String is under 'a*b+'\n";
    else if(is_abb(s)) cout << "String is under 'abb'\n";
    else cout << "String is not recognized\n";
    return 0;
}