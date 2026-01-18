#include <bits/stdc++.h>
using namespace std;

// Structure to store a production
struct Production {
    string lhs;
    vector<string> rhs;
};

int n; // number of productions
vector<Production> prods;

map<string, set<string>> firstSet;  // FIRST sets
map<string, set<string>> followSet; // FOLLOW sets
set<string> nonTerminals;
set<string> terminals;

// Utility: check if a symbol is non-terminal
bool isNonTerminal(const string &s) {
    return s.length() == 1 && isupper(s[0]);
}

// Compute FIRST set for a symbol (recursive)
set<string> computeFirst(const string &symbol) {
    // Terminal or epsilon
    if (!isNonTerminal(symbol)) return {symbol};
    if (!firstSet[symbol].empty()) return firstSet[symbol];

    for (auto &p : prods) {
        if (p.lhs != symbol) continue;
        for (auto &alt : p.rhs) {
            stringstream ss(alt);
            vector<string> symbols;
            string temp;
            size_t i = 0;
            while (i < alt.size()) {
                if (alt[i] == '(' || alt[i] == ')' || alt[i] == '+' || alt[i] == '*') {
                    symbols.push_back(string(1, alt[i]));
                    i++;
                } else if (i+1 < alt.size() && alt.substr(i,2)=="id") {
                    symbols.push_back("id");
                    i+=2;
                } else if (alt[i]=='#') {
                    symbols.push_back("#");
                    i++;
                } else if (isupper(alt[i])) {
                    symbols.push_back(string(1,alt[i]));
                    i++;
                } else i++; // skip invalid
            }

            bool epsilon = true;
            for (auto &sym : symbols) {
                auto firstSym = computeFirst(sym);
                for (auto &s : firstSym)
                    if (s != "#") firstSet[symbol].insert(s);
                if (firstSym.count("#")==0) {
                    epsilon = false;
                    break;
                }
            }
            if (epsilon) firstSet[symbol].insert("#");
        }
    }
    return firstSet[symbol];
}

// Compute FOLLOW sets iteratively
void computeFollow() {
    followSet[prods[0].lhs].insert("$"); // start symbol
    bool changed;
    do {
        changed = false;
        for (auto &p : prods) {
            for (auto &alt : p.rhs) {
                vector<string> symbols;
                size_t i = 0;
                while (i < alt.size()) {
                    if (alt[i] == '(' || alt[i] == ')' || alt[i] == '+' || alt[i] == '*') {
                        symbols.push_back(string(1, alt[i]));
                        i++;
                    } else if (i+1 < alt.size() && alt.substr(i,2)=="id") {
                        symbols.push_back("id");
                        i+=2;
                    } else if (alt[i]=='#') {
                        symbols.push_back("#");
                        i++;
                    } else if (isupper(alt[i])) {
                        symbols.push_back(string(1,alt[i]));
                        i++;
                    } else i++;
                }

                for (int j=0;j<symbols.size();j++) {
                    string B = symbols[j];
                    if (!isNonTerminal(B)) continue;
                    bool epsilon=true;
                    for (int k=j+1;k<symbols.size();k++) {
                        epsilon=false;
                        string sym = symbols[k];
                        auto firstSym = computeFirst(sym);
                        for (auto &s : firstSym) if (s!="#") changed |= followSet[B].insert(s).second;
                        if (firstSym.count("#")) epsilon=true;
                        else break;
                    }
                    if (epsilon) {
                        for (auto &s : followSet[p.lhs]) changed |= followSet[B].insert(s).second;
                    }
                }
            }
        }
    } while (changed);
}

int main() {
    cout << "Enter number of productions: ";
    cin >> n;
    prods.resize(n);
    cin.ignore();

    cout << "Enter productions (format A->α|β, use # for epsilon):\n";
    for (int i=0;i<n;i++) {
        string prod;
        getline(cin,prod);
        string lhs = prod.substr(0,1);
        prods[i].lhs = lhs;
        nonTerminals.insert(lhs);
        string rhsStr = prod.substr(3);
        stringstream ss(rhsStr);
        string alt;
        while (getline(ss,alt,'|')) {
            prods[i].rhs.push_back(alt);
        }
    }

    // Collect terminals
    for (auto &p : prods) {
        for (auto &alt : p.rhs) {
            size_t i=0;
            while (i < alt.size()) {
                if (alt[i] == '(' || alt[i] == ')' || alt[i] == '+' || alt[i] == '*') {
                    terminals.insert(string(1,alt[i]));
                    i++;
                } else if (i+1 < alt.size() && alt.substr(i,2)=="id") {
                    terminals.insert("id");
                    i+=2;
                } else if (alt[i]=='#') {
                    i++;
                } else if (isupper(alt[i])) {
                    i++;
                } else i++;
            }
        }
    }

    // Compute FIRST sets
    for (auto &nt : nonTerminals) computeFirst(nt);

    cout << "\nFIRST sets:\n";
    for (auto &nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (auto &s : firstSet[nt]) cout << s << " ";
        cout << "}\n";
    }

    // Compute FOLLOW sets
    computeFollow();
    cout << "\nFOLLOW sets:\n";
    for (auto &nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (auto &s : followSet[nt]) cout << s << " ";
        cout << "}\n";
    }

    // Construct LL(1) Parsing Table
    cout << "\nLL(1) Parsing Table:\n";
    for (auto &p : prods) {
        for (auto &alt : p.rhs) {
            vector<string> symbols;
            size_t i=0;
            while (i<alt.size()) {
                if (alt[i] == '(' || alt[i] == ')' || alt[i] == '+' || alt[i] == '*') {
                    symbols.push_back(string(1,alt[i])); i++;
                } else if (i+1<alt.size() && alt.substr(i,2)=="id") { symbols.push_back("id"); i+=2; }
                else if (alt[i]=='#') { symbols.push_back("#"); i++; }
                else if (isupper(alt[i])) { symbols.push_back(string(1,alt[i])); i++; }
                else i++;
            }

            set<string> firstAlpha;
            bool epsilon=true;
            for (auto &sym : symbols) {
                auto f = computeFirst(sym);
                for (auto &s : f) if (s!="#") firstAlpha.insert(s);
                if (f.count("#")==0) { epsilon=false; break; }
            }
            if (epsilon) firstAlpha.insert("#");

            for (auto &a : firstAlpha) {
                if (a!="#") cout << "M[" << p.lhs << "," << a << "] = " << p.lhs << "->" << alt << "\n";
                else for (auto &b : followSet[p.lhs])
                        cout << "M[" << p.lhs << "," << b << "] = " << p.lhs << "->" << alt << "\n";
            }
        }
    }

    return 0;
}
