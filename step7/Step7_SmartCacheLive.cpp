#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sstream>
#endif

using namespace std;

// 🟢 Function to get live memory pages from the system
vector<int> getLiveMemoryPages(int count) {
    vector<int> pages;

#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        size_t pageSize = 4096; // Windows page size
        size_t totalPages = memInfo.WorkingSetSize / pageSize;
        for (int i = 0; i < count; i++) {
            pages.push_back(rand() % totalPages + 1);
        }
    }
#else
    ifstream file("/proc/self/statm");
    size_t totalPages;
    file >> totalPages;
    for (int i = 0; i < count; i++) {
        pages.push_back(rand() % totalPages + 1);
    }
#endif

    return pages;
}

// 🟢 FIFO Page Replacement
int fifoPageReplacement(const vector<int>& pages, int capacity) {
    queue<int> cache;
    unordered_map<int, bool> pageTable;
    int pageFaults = 0;

    for (int page : pages) {
        if (!pageTable[page]) {
            if (cache.size() == capacity) {
                int removed = cache.front();
                cache.pop();
                pageTable.erase(removed);
            }
            cache.push(page);
            pageTable[page] = true;
            pageFaults++;
        }
    }
    return pageFaults;
}

// 🟢 LRU Page Replacement
int lruPageReplacement(const vector<int>& pages, int capacity) {
    list<int> cache;
    unordered_map<int, list<int>::iterator> pageTable;
    int pageFaults = 0;

    for (int page : pages) {
        if (pageTable.find(page) == pageTable.end()) { 
            if (cache.size() == capacity) {
                int removed = cache.back();
                cache.pop_back();
                pageTable.erase(removed);
            }
            cache.push_front(page);
            pageTable[page] = cache.begin();
            pageFaults++;
        } else { 
            cache.erase(pageTable[page]);
            cache.push_front(page);
            pageTable[page] = cache.begin();
        }
    }
    return pageFaults;
}

// 🟢 Optimal Page Replacement
int optimalPageReplacement(const vector<int>& pages, int capacity) {
    vector<int> cache;
    int pageFaults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (find(cache.begin(), cache.end(), page) != cache.end()) {
            continue;
        }

        if (cache.size() < capacity) {
            cache.push_back(page);
        } else {
            int farthest = -1, indexToReplace = -1;
            for (size_t j = 0; j < cache.size(); j++) {
                size_t k;
                for (k = i + 1; k < pages.size(); k++) {
                    if (cache[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            indexToReplace = j;
                        }
                        break;
                    }
                }
                if (k == pages.size()) {
                    indexToReplace = j;
                    break;
                }
            }
            cache[indexToReplace] = page;
        }
        pageFaults++;
    }
    return pageFaults;
}

// 🟢 Main Function
int main() {
    cout << "========================================\n";
    cout << "        🚀 Live SmartCache Simulator   \n";
    cout << "========================================\n";

    int sequenceSize;
    cout << "Enter the number of memory pages to monitor: ";
    cin >> sequenceSize;

    vector<int> pages = getLiveMemoryPages(sequenceSize);

    cout << "\n🔴 Live Page Reference Sequence: ";
    for (int page : pages) cout << page << " ";
    cout << endl;

    int cacheSize;
    cout << "Enter Cache Size: ";
    cin >> cacheSize;

    // Run all algorithms
    int fifoFaults = fifoPageReplacement(pages, cacheSize);
    int lruFaults = lruPageReplacement(pages, cacheSize);
    int optimalFaults = optimalPageReplacement(pages, cacheSize);

    // Show results
    cout << "\n📊 Page Faults:\n";
    cout << "FIFO: " << fifoFaults << endl;
    cout << "LRU: " << lruFaults << endl;
    cout << "Optimal: " << optimalFaults << endl;

    // Save results to a file for Python graphing
    ofstream file("page_faults.txt");
    file << fifoFaults << " " << lruFaults << " " << optimalFaults;
    file.close();

    // Call Python script to generate a graph
    system("python3 plot_graph.py");

    return 0;
}
