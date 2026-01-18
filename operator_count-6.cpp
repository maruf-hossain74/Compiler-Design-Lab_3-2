#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cout << "Enter a string:\n";
    getline(cin, s);

    vector<string> operators = {
        ">>=", "<<=", "++", "--", "==", "!=", "<=", ">=",
        "&&", "||", "+=", "-=", "*=", "/=", "%=",
        "&=", "|=", "^=", "<<", ">>", "->",
        "+", "-", "*", "/", "%", "<", ">", "=", "!",
        "&", "|", "^", "~", "?", ":", "."
    };

    int count = 0;

    for (int i = 0; i < s.length(); ) {
        bool matched = false;

        for (string op : operators) {
            int len = op.length();
            if (s.substr(i, len) == op) {
                count++;
                i += len;
                matched = true;
                break;
            }
        }

        if (!matched) i++;
    }

    cout << "Total number of operators: " << count << endl;
    return 0;
}
