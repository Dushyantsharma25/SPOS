#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<fstream>
#include<utility>  

using namespace std;

int main() {

    vector<pair<int, string>> s;   // (srno., name);
    vector<pair<int, string>> l;   // (srno., name);
    
    vector<string> MOT = {"LOAD", "STORE", "ADD", "SUB", "JMP", "HLT"};
    vector<string> POT = {"START", "END", "DC", "DS", "LTORG"};
    
    vector<pair<pair<int, string>, pair<int, string>>> m;        
    vector<pair<int, string>> p;
    
    ifstream a;
    a.open("base.asm");  // Changed to ifstream to read the file
    
    string h;
    int i = 0, j = 0, k = 0, y = 0;
    
    while(getline(a, h)) {  
        
        int x = h.length();
        
        // For symbol table entry (lines with ':')
        if (h.find(":") != string::npos) {
            i++;
            size_t z = find(h.begin(), h.end(), ':') - h.begin();  // Corrected this to get the position
            s.push_back(make_pair(i, h.substr(0, z)));
        }
        // For literal table entry (lines with ' equ ')
        else if (h.find(" equ ") != string::npos) {  
            j++;
            size_t z = h.find(" equ ");
            l.push_back(make_pair(j, h.substr(0,z)));  // Corrected this to capture the literal part after " equ "
        }
        // For machine and pseudo op codes
        else {
           
            for (int g = 0; g < MOT.size(); g++) {
                if (h.find(MOT[g]) != string::npos) {  
                    k++;
                    m.push_back(make_pair(make_pair(k, MOT[g]), make_pair(1, "is")));
                }
            }
            
            for (int g = 0; g < POT.size(); g++) {
                if (h.find(POT[g]) != string::npos) {  
                    y++;
                    m.push_back(make_pair(make_pair(y, POT[g]), make_pair(1, "is")));  // Corrected this
                }
            }
        }
    }

    a.close();
    
    // Printing Symbol Table (s)
    cout << "Symbol Table (s):\n";
    cout << "SrNo\tName\n";
    for (auto entry : s) {
        cout << entry.first << "\t" << entry.second << "\n";
    }
    cout << endl;

    // Printing Literal Table (l)
    cout << "Literal Table (l):\n";
    cout << "SrNo\tLiteral\n";
    for (auto entry : l) {
        cout << entry.first << "\t" << entry.second << "\n";
    }
    cout << endl;

    // Printing Machine Op Code Table (m)
    cout << "Machine Op Code Table (m):\n";
    cout << "SrNo\tname\tlength\ttype\n";
    for (auto entry : m) {
        cout << entry.first.first << "\t" << entry.first.second << "\t" << entry.second.first << "\t" << entry.second.second << "\n";
    }
    cout << endl;

    // Printing the p vector Pseudo op code Table(p)
    cout << "P Table (p):\n";
    cout << "SrNo\tName\n";
    for (auto entry : p) {
        cout << entry.first << "\t" << entry.second << "\n";
    }
    cout << endl;
    
    return 0;
}

