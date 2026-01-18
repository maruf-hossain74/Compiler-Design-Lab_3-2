#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;
bool isKeyword(const string& s) {
    string keywords[] = {"int", "float", "if", "else", "while", "return"};
    for (string k : keywords)
        if (s == k) return true;
    return false;
}
int main() {
    ifstream fin("input.txt");
    char ch;
    string token;
    if (!fin) {
        cout << "Error opening file!" << endl;
        return 1;
    }
    while (fin.get(ch)) {
        if (isspace(ch)) continue;
        if (ch == '/') {
            char next = fin.peek();
            if (next == '/') {
                while (fin.get(ch) && ch != '\n');
                continue;
            }
            else if (next == '*') {
                fin.get(); // consume '*'
                while (fin.get(ch)) {
                    if (ch == '*' && fin.peek() == '/') {
                        fin.get(); // consume '/'
                        break;
                    }
                }
                continue;
            }
            else {
                cout << "Operator: /" << endl;
                continue;
            }
        }
        if (isalpha(ch) || ch == '_') {
            token = ch;
            while (isalnum(fin.peek()) || fin.peek() == '_') {
                fin.get(ch);
                token += ch;
            }
            if (isKeyword(token))
                cout << "Keyword: " << token << endl;
            else
                cout << "Identifier: " << token << endl;
        }
        else if (isdigit(ch)) {
            token = ch;
            while (isdigit(fin.peek())) {
                fin.get(ch);
                token += ch;
            }
            cout << "Number: " << token << endl;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '=' || ch == '<' || ch == '>') {
            cout << "Operator: " << ch << endl;
        }
        else if (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            cout << "Separator: " << ch << endl;
        }
        else {
            cout << "Unknown symbol: " << ch << endl;
        }
    }
    fin.close();
    return 0;
}
