
v = int(raw_input())
n = int(raw_input())
a = [int(raw_input()) for i in range(0, n)]
f = [0 for i in range(0, v + 1)]
f[0] = 1

for i in range(0, n):
    for j in range(v, a[i]-1, -1):
        if f[j - a[i]] > 0:
            f[j] = 1

ans = v
for i in range(0, v + 1):
    if f[i] > 0 and v - i < ans:
        ans = v - i
print ans
