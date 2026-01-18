#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    int count = 0;
    cout << "Enter a string: ";
    getline(cin, s);
    for (char c : s) {
        if (c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '%' || c == '=' || c == '<' || c == '>' ||
            c == '!' || c == '&' || c == '|' || c == '^') {
            count++;
        }
    }
    cout << "Number of operators: " << count << endl;
    return 0;
}
