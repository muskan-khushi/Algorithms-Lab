import matplotlib.pyplot as plt

# Data from the output
input_sizes = [100, 500, 1000, 5000, 10000]
execution_times = [61, 340, 1106, 5403, 23322]

# Plotting the graph
plt.figure(figsize=(8, 6))
plt.plot(input_sizes, execution_times, marker='o', linestyle='-', color='b')

# Adding labels and title
plt.xlabel('Input Size (Number of Jobs)')
plt.ylabel('Execution Time (µs)')
plt.title('Job Sequencing: Input Size vs Execution Time')
plt.grid(True)
plt.show()
