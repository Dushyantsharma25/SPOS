#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ---------- FIFO Page Replacement Function ----------
void fifoPageReplacement(vector<int> pages, int frameCount) {
    vector<int> frames;
    queue<int> fifoQueue;
    int pageFaults = 0;

    cout << "\n--- FIFO Page Replacement Simulation ---\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        bool found = false;

        // Check if page is already in frames (HIT)
        for (int f : frames)
            if (f == page)
                found = true;

        if (!found) {
            pageFaults++;

            // If all frames are full, remove the oldest page
            if (frames.size() == frameCount) {
                int oldPage = fifoQueue.front();
                fifoQueue.pop();

                // Replace old page with new one
                for (int j = 0; j < frames.size(); j++) {
                    if (frames[j] == oldPage) {
                        frames[j] = page;
                        break;
                    }
                }
            } else {
                // Still space left in frames
                frames.push_back(page);
            }

            fifoQueue.push(page);
        }

        // Display current step
        cout << "Step " << i + 1 << " (Page " << page << "): ";
        for (int f : frames)
            cout << f << " ";
        cout << (found ? "(Hit)" : "(Miss)") << endl;
    }

    cout << "\nTotal Page Faults: " << pageFaults << endl;
    cout << "Total Page Hits: " << pages.size() - pageFaults << endl;
}

// ---------- Main Function ----------
int main() {
    int n, frameCount;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> frameCount;

    // Call the FIFO page replacement function
    fifoPageReplacement(pages, frameCount);

    return 0;
}
