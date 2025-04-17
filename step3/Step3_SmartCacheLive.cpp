#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <list>
#include <unordered_set>
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

int lruPageReplacement(const vector<int>& pages, int capacity) {
    list<int> cache;
    unordered_map<int, list<int>::iterator> pageTable;
    int faults = 0;
    for (int page : pages) {
        if (pageTable.find(page) == pageTable.end()) {
            if (cache.size() == capacity) {
                int last = cache.back();
                cache.pop_back();
                pageTable.erase(last);
            }
            cache.push_front(page);
            pageTable[page] = cache.begin();
            faults++;
        } else {
            cache.erase(pageTable[page]);
            cache.push_front(page);
            pageTable[page] = cache.begin();
        }
    }
    return faults;
}

int optimalPageReplacement(const vector<int>& pages, int capacity) {
    unordered_set<int> cache;
    int faults = 0;
    for (size_t i = 0; i < pages.size(); i++) {
        if (cache.find(pages[i]) == cache.end()) {
            if (cache.size() == capacity) {
                int farthest = i + 1, index = -1;
                for (int p : cache) {
                    size_t j = i + 1;
                    while (j < pages.size() && pages[j] != p)
                        j++;
                    if (j > farthest) {
                        farthest = j;
                        index = p;
                    }
                }
                cache.erase(index == -1 ? *cache.begin() : index);
            }
            cache.insert(pages[i]);
            faults++;
        }
    }
    return faults;
}

int main() {
    vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    cout << "FIFO: " << fifoPageReplacement(pages, 3) << endl;
    cout << "LRU: " << lruPageReplacement(pages, 3) << endl;
    cout << "Optimal: " << optimalPageReplacement(pages, 3) << endl;
    return 0;
}
