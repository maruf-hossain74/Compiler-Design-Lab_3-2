#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, string> grammar;
    int n;
    cout << "Enter number of grammar rules: ";
    cin >> n;
    cin.ignore();

    cout << "Enter grammar in format: NonTerminal->Production\n";
    for(int i = 0; i < n; i++){
        string rule;
        getline(cin, rule);
        size_t pos = rule.find("->");
        if(pos != string::npos){
            string nt = rule.substr(0,pos);
            string prod = rule.substr(pos+2);
            grammar[nt] = prod;
        }

    }

    string input;
    cout << "Enter the input string: ";
    getline(cin, input);

    stack<string> st;
    st.push("$");
    st.push("E");

    int i = 0;
    while(!st.empty()){
        string top = st.top();
        string curr = (i < input.size()) ? string(1, input[i]) : "$";

        if(top == "$" && curr == "$") break;

        if(top == curr){
            st.pop();
            i++;
        } else if(grammar.find(top) != grammar.end()){
            st.pop();
            string prod = grammar[top];
            if(prod != "e"){
                for(int j = prod.size()-1; j >= 0; j--) st.push(string(1, prod[j]));
            }
        } else {
            cout << "String not accepted.\n";
            return 0;
        }
    }

    if(i == input.size()) cout << "String accepted by LL(1) parser.\n";
    else cout << "String not accepted.\n";

    return 0;
}