#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int fifoPageReplacement(const vector<int>& pages, int capacity) {
    queue<int> cache;
    unordered_map<int, bool> pageTable;
    int faults = 0;

    for (int page : pages) {
        if (!pageTable[page]) {
            if (cache.size() == capacity) {
                int removed = cache.front();
                cache.pop();
                pageTable.erase(removed);
            }
            cache.push(page);
            pageTable[page] = true;
            faults++;
        }
    }
    return faults;
}

int main() {
    vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int faults = fifoPageReplacement(pages, 3);
    cout << "FIFO Page Faults: " << faults << endl;
    return 0;
}
