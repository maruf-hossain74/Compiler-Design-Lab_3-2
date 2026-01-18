#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string op;
    cin >> op;
    vector<string> ops = {"+","-","*","/","%","==","!=", "<", ">", "<=", ">=", "&&", "||", "!", "=", "+=", "-=", "*=", "/="};
    if (find(ops.begin(), ops.end(), op) != ops.end()) cout << op << " is a valid operator\n";
    else cout << op << " is not a valid operator\n";
    return 0;
}