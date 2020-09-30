# input generator
n = 500
edges = []
for w in range(1, 5):
    for i in range(n):
        if i + w < n: edges.append((i, i+w, w))
print(n, len(edges))
print(0, n-1)
for u, v, w in edges:
    print(u, v, w)
print(0, 0)

# output
-1
