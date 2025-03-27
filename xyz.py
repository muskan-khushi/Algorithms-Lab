import time
import random
import heapq
import matplotlib.pyplot as plt

# Dijkstra's algorithm implementation
def dijkstra(graph, src, V):
    dist = [float('inf')] * V
    dist[src] = 0
    pq = [(0, src)]  # (distance, node)
    
    while pq:
        d, u = heapq.heappop(pq)
        
        if d > dist[u]:
            continue
        
        for v, weight in graph[u]:
            if dist[u] + weight < dist[v]:
                dist[v] = dist[u] + weight
                heapq.heappush(pq, (dist[v], v))
    
    return dist

# Function to generate a random graph
def generate_graph(V, density=0.3):
    graph = {i: [] for i in range(V)}
    for i in range(V):
        for j in range(i + 1, V):
            if random.random() < density:  # Density determines edge probability
                weight = random.randint(1, 20)
                graph[i].append((j, weight))
                graph[j].append((i, weight))
    return graph

# Experiment: Run Dijkstra on different input sizes
sizes = [10, 50, 100, 200, 500, 1000]  # Different graph sizes
times = []

for V in sizes:
    graph = generate_graph(V, density=0.3)
    start_time = time.time()
    dijkstra(graph, 0, V)  # Run Dijkstra from source 0
    end_time = time.time()
    
    times.append(end_time - start_time)

# Plot the graph
plt.figure(figsize=(8, 5))
plt.plot(sizes, times, marker='o', linestyle='-', color='b', label="Dijkstra's Algorithm")
plt.xlabel("Number of Nodes (V)")
plt.ylabel("Execution Time (seconds)")
plt.title("Dijkstra's Algorithm Execution Time vs Input Size")
plt.legend()
plt.grid(True)
plt.show()
