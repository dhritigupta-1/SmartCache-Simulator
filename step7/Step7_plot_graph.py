import matplotlib.pyplot as plt

# Read page faults data from file
with open("page_faults.txt", "r") as file:
    data = file.read().split()
    fifo_faults = int(data[0])
    lru_faults = int(data[1])
    optimal_faults = int(data[2])

# Labels and values
algorithms = ["FIFO", "LRU", "Optimal"]
page_faults = [fifo_faults, lru_faults, optimal_faults]

# Create bar graph
plt.figure(figsize=(8, 5))
plt.bar(algorithms, page_faults, color=["red", "blue", "green"])
plt.xlabel("Page Replacement Algorithms")
plt.ylabel("Page Faults")
plt.title("SmartCache Page Faults Comparison")
plt.show()
