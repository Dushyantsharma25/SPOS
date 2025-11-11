#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// -------------------- FIRST FIT --------------------
void firstFit(vector<int> blockSize, vector<int> processSize) {
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++) {
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break; // stop after first suitable block
            }
        }
    }

    cout << "\n--- First Fit Allocation ---\n";
    for (int i = 0; i < processSize.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

// -------------------- BEST FIT --------------------
void bestFit(vector<int> blockSize, vector<int> processSize) {
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\n--- Best Fit Allocation ---\n";
    for (int i = 0; i < processSize.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

// -------------------- WORST FIT --------------------
void worstFit(vector<int> blockSize, vector<int> processSize) {
    vector<int> allocation(processSize.size(), -1);

    for (int i = 0; i < processSize.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "\n--- Worst Fit Allocation ---\n";
    for (int i = 0; i < processSize.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

// -------------------- NEXT FIT --------------------
void nextFit(vector<int> blockSize, vector<int> processSize) {
    vector<int> allocation(processSize.size(), -1);
    int j = 0; // remembers last allocated position

    for (int i = 0; i < processSize.size(); i++) {
        int count = 0;
        while (count < blockSize.size()) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % blockSize.size(); // circular traversal
            count++;
        }
    }

    cout << "\n--- Next Fit Allocation ---\n";
    for (int i = 0; i < processSize.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " -> Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " -> Not Allocated\n";
    }
}

// -------------------- MAIN FUNCTION --------------------
int main() {
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};

    // Make copies for each algorithm
    vector<int> b1 = blockSize;
    vector<int> b2 = blockSize;
    vector<int> b3 = blockSize;
    vector<int> b4 = blockSize;

    firstFit(b1, processSize);
    bestFit(b2, processSize);
    worstFit(b3, processSize);
    nextFit(b4, processSize);

    return 0;
}
