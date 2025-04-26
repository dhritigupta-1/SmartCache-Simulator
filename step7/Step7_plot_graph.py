import matplotlib.pyplot as plt
import numpy as np
from matplotlib import style
import matplotlib.patches as mpatches

# Use a stylish theme
style.use('ggplot')

# Read page faults data from file
with open("page_faults.txt", "r") as file:
    data = file.read().split()
    fifo_faults = int(data[0])
    lru_faults = int(data[1])
    optimal_faults = int(data[2])

# Data setup
algorithms = ["FIFO", "LRU", "Optimal"]
page_faults = [fifo_faults, lru_faults, optimal_faults]
colors = ['#FF6B6B', '#4ECDC4', '#45B7D1']
patterns = ['//', '..', 'xx']

# Create figure with multiple subplots
plt.figure(figsize=(14, 10), facecolor='#f5f5f5')
plt.suptitle('SmartCache Performance Analysis', fontsize=18, fontweight='bold', y=0.98)

# 1. Main Bar Chart
plt.subplot(2, 2, 1)
bars = plt.bar(algorithms, page_faults, color=colors, edgecolor='black', 
               linewidth=1.2, hatch=patterns, alpha=0.9)

# Add value labels on bars
for bar in bars:
    height = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2., height,
             f'{height}',
             ha='center', va='bottom', fontsize=12)

plt.title('Page Faults Comparison', pad=15)
plt.ylabel('Number of Page Faults', labelpad=10)
plt.grid(axis='y', linestyle='--', alpha=0.7)

# 2. Pie Chart
plt.subplot(2, 2, 2)
explode = (0.05, 0.05, 0.05)
plt.pie(page_faults, labels=algorithms, autopct='%1.1f%%',
        startangle=140, colors=colors, explode=explode,
        shadow=True, wedgeprops={'edgecolor': 'black', 'linewidth': 1})
plt.title('Page Faults Distribution', pad=15)

# 3. Horizontal Bar Chart (for efficiency) - FIXED SYNTAX HERE
plt.subplot(2, 2, 3)
max_faults = max(page_faults)
efficiency = [100 - (faults/max_faults)*100 for faults in page_faults]
hbars = plt.barh(algorithms, efficiency, color=colors, edgecolor='black', 
                hatch=patterns, alpha=0.9)

# Add value labels
for bar in hbars:
    width = bar.get_width()
    plt.text(width + 1, bar.get_y() + bar.get_height()/2,
             f'{width:.1f}%',
             va='center', fontsize=11)

plt.title('Cache Efficiency (Higher is Better)', pad=15)
plt.xlabel('Efficiency Percentage', labelpad=10)
plt.xlim(0, 110)
plt.grid(axis='x', linestyle='--', alpha=0.7)

# 4. Line Plot Comparison
plt.subplot(2, 2, 4)
x = np.arange(len(algorithms))
plt.plot(x, page_faults, 'o-', linewidth=2, markersize=10, color='#FF9F1C')
plt.xticks(x, algorithms)
plt.title('Page Faults Comparison', pad=15)
plt.ylabel('Page Faults', labelpad=10)
plt.ylim(0, max(page_faults)*1.1)
plt.grid(True, linestyle='--', alpha=0.7)

# Add custom legend
legend_elements = [
    mpatches.Patch(facecolor=colors[0], edgecolor='black', hatch=patterns[0], label='FIFO'),
    mpatches.Patch(facecolor=colors[1], edgecolor='black', hatch=patterns[1], label='LRU'),
    mpatches.Patch(facecolor=colors[2], edgecolor='black', hatch=patterns[2], label='Optimal')
]
plt.figlegend(handles=legend_elements, loc='lower center', 
              ncol=3, bbox_to_anchor=(0.5, -0.02),
              fontsize=12, framealpha=1)

# Adjust layout and save
plt.tight_layout()
plt.savefig('smartcache_analysis.png', dpi=300, bbox_inches='tight')

# Show the plots
plt.show()
