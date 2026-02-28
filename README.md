# 🚀 SmartCache Simulator

🔗 **Live Website:**  
👉 [Smart-Cache](https://smart-cache.netlify.app/)

SmartCache is a C++ project that simulates and compares three classic page replacement algorithms:
- FIFO (First-In-First-Out)
- LRU (Least Recently Used)
- Optimal (Best-case strategy)

It dynamically generates a memory reference string using system memory stats and visualizes results using Python!

## 🔧 Features

- Live memory page simulation
- Page Fault comparison across 3 algorithms
- Bar chart visualization using Python & Matplotlib

## 📦 Files

| File             | Description                                |
|------------------|--------------------------------------------|
| `SmartCacheLive.cpp` | Main C++ program for simulation             |
| `plot_graph.py`  | Python script to visualize page faults     |
| `page_faults.txt`| Auto-generated results file                |

## 🖥️ Usage

1. Compile and run:
   ```bash
   g++ SmartCacheLive.cpp -o SmartCacheLive
   ./SmartCacheLive
2. Enter the number of memory pages and cache size.

3. See console results and a bar graph (requires Python & matplotlib).

## 📈 Output

- Console Output: Total page faults by algorithm
- Graph: Visual bar chart of page fault comparison


## OS Memory Management

File I/O (C++ & Python)

Cross-language integration (C++ to Python)

## 🐍 Python Dependencies
```bash
pip install matplotlib
