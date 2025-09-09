#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

int main() {
    vector<pair<int, pair<string,int>>> MNT;   // (MNTC, macro name, MDTC)
    vector<pair<int, string>> MDT;             // (MDTC, macro definition line)
    unordered_map<string, int> macroNameToMNTC; // For quick lookup

    struct ALAEntry {
        int mntc;
        int index;
        string formal;
        string actual;
    };

    vector<ALAEntry> ALA;    // Stores all ALA entries

    ifstream a("Ass.asm");

    string line;
    int MNTC = 0;
    int MDTC = 1; // Start MDT counter from 1

    bool isMacro = false;

    // First pass: read macros and build MNT, MDT
    while(getline(a, line)) {
        if (line.find("%macro") != string::npos) {
            MNTC++;

            // Extract macro name and number of args
            istringstream iss(line);
            string temp, macroName;
            int numArgs = 0;

            iss >> temp >> macroName >> numArgs;

            MNT.push_back(make_pair(MNTC, make_pair(macroName, MDTC)));
            macroNameToMNTC[macroName] = MNTC;

            isMacro = true;
            continue;
        }

        if (isMacro) {
            MDT.push_back(make_pair(MDTC++, line));
            if (line.find("%endmacro") != string::npos) {
                isMacro = false;
            }
        }
    }

    a.clear();
    a.seekg(0);

    // Second pass: parse macro invocations in the code after macros
    while(getline(a, line)) {
        // Skip empty lines and lines starting with %macro or %endmacro
        if (line.find("%macro") != string::npos || line.find("%endmacro") != string::npos) {
            continue;
        }

        // Check if line contains macro invocation
        istringstream iss(line);
        string firstWord;
        iss >> firstWord;

        // If first word is a macro name from MNT, parse arguments
        if (macroNameToMNTC.find(firstWord) != macroNameToMNTC.end()) {
            int currentMNTC = macroNameToMNTC[firstWord];

            // Get the rest of the line as arguments string
            string argsLine;
            getline(iss, argsLine);

            // Remove leading spaces and commas
            // Tokenize actual arguments by comma
            vector<string> actualArgs;
            string arg;
            stringstream ss(argsLine);
            while (getline(ss, arg, ',')) {
                // Trim spaces
                size_t start = arg.find_first_not_of(" \t");
                size_t end = arg.find_last_not_of(" \t");
                if (start != string::npos && end != string::npos)
                    arg = arg.substr(start, end - start + 1);
                else
                    arg = "";

                if (!arg.empty()) {
                    actualArgs.push_back(arg);
                }
            }

            // Add to ALA: map formal args (%1, %2...) to actual arguments
            for (int i = 0; i < (int)actualArgs.size(); i++) {
                ALAEntry entry;
                entry.mntc = currentMNTC;
                entry.index = i + 1;
                entry.formal = "%" + to_string(i + 1);
                entry.actual = actualArgs[i];
                ALA.push_back(entry);
            }
        }
    }

    a.close();

    // Display MNT
    cout << "MNT (Macro Name Table):\n";
    cout << "MNTC --> MACRO NAME --> MDTC\n";
    for (auto &entry : MNT) {
        cout << entry.first << "    --> " << entry.second.first << "   --> " << entry.second.second << "\n";
    }
    
    // Display MDT
    cout << "\nMDT (Macro Definition Table):\n";
    cout << "MDTC --> Macro Definition Line\n";
    for (auto &entry : MDT) {
        cout << entry.first << "    --> " << entry.second << "\n";
    }

    // Display ALA
    cout << "\nALA (Argument List Array):\n";
    cout << "Index --> Formal --> Actual\n";
    for (auto &entry : ALA) {
        cout<< entry.index << "     --> " << entry.formal << "     --> " << entry.actual << "\n";
    }
    
    return 0;
}
