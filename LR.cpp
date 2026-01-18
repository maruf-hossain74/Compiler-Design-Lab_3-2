#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

struct Production {
    string lhs;
    vector<string> rhs;
};

vector<string> tokenize(const string &s) {
    vector<string> tokens;
    int i = 0, n = s.size();
    while(i < n) {
        if(isspace((unsigned char)s[i])) { i++; continue; }
        if(isalpha((unsigned char)s[i])) {
            string t;
            while(i < n && isalpha((unsigned char)s[i])) { t.push_back(s[i]); i++; }
            tokens.push_back(t);
        } else {
            string t(1, s[i]);
            tokens.push_back(t);
            i++;
        }
    }
    return tokens;
}

bool endsWith(const vector<string> &stackVec, const vector<string> &pat) {
    if(pat.empty()) return true;
    if(stackVec.size() < pat.size()) return false;
    size_t s = stackVec.size(), p = pat.size();
    for(size_t i = 0; i < p; ++i)
        if(stackVec[s - p + i] != pat[i]) return false;
    return true;
}

int main() {
    while(true) {
        int n;
        cout << "Enter number of grammar rules (or 0 to exit): ";
        if(!(cin >> n)) return 0;
        if(n == 0) return 0;
        cin.ignore();

        vector<Production> grammar;
        unordered_map<string, vector<int>> prodMap;

        cout << "Enter grammar rules:\n";
        for(int i = 0; i < n; i++) {
            string rule;
            getline(cin, rule);
            size_t pos = rule.find("->");
            if(pos == string::npos) { --i; continue; }
            string lhs = rule.substr(0, pos);
            string rhs_raw = rule.substr(pos + 2);
            auto trim = [](string s)->string {
                size_t a = 0;
                while(a < s.size() && isspace((unsigned char)s[a])) a++;
                size_t b = s.size();
                while(b > a && isspace((unsigned char)s[b-1])) b--;
                return s.substr(a, b-a);
            };
            lhs = trim(lhs);
            rhs_raw = trim(rhs_raw);
            Production p;
            p.lhs = lhs;
            if(rhs_raw == "e" || rhs_raw.empty()) p.rhs = {};
            else p.rhs = tokenize(rhs_raw);
            grammar.push_back(p);
            prodMap[lhs].push_back((int)grammar.size()-1);
        }

        string inputLine;
        cout << "Enter the input string: ";
        getline(cin, inputLine);
        if(inputLine.empty()) continue;

        vector<string> inputTokens = tokenize(inputLine);
        inputTokens.push_back("$");

        vector<string> stVec;
        stVec.push_back("$");

        string startSymbol = grammar[0].lhs;
        size_t ip = 0;
        bool accepted = false, error = false;
        int stepCount = 0, MAX_STEPS = 10000;

        while(stepCount++ < MAX_STEPS) {
            if(stVec.size() == 2 && stVec[0] == "$" && stVec[1] == startSymbol && ip < inputTokens.size() && inputTokens[ip] == "$") {
                accepted = true;
                break;
            }

            bool reduced = false;
            for(size_t pi = 0; pi < grammar.size(); ++pi) {
                const Production &P = grammar[pi];
                if(endsWith(stVec, P.rhs)) {
                    if(!P.rhs.empty())
                        for(size_t k = 0; k < P.rhs.size(); ++k) stVec.pop_back();
                    stVec.push_back(P.lhs);
                    reduced = true;
                    break;
                }
            }

            if(reduced) continue;

            if(ip < inputTokens.size()) {
                string tok = inputTokens[ip];
                if(tok == "$") { error = true; break; }
                stVec.push_back(tok);
                ip++;
                continue;
            }

            error = true;
            break;
        }

        if(stepCount >= MAX_STEPS) cout << "Parsing aborted.\n";
        else if(accepted) cout << "String accepted by the shift-reduce parser.\n";
        else cout << "String not accepted.\n";
    }
}