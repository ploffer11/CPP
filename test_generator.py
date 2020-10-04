import random

MAX = 200000
print(MAX)
for i in range(MAX):
    print(random.randint(1, (1 << 30) - 10), sep=" ")