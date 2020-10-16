
def fac(n):
    if n == 1:
        return 1
    else:
        return n * fac(n - 1)

n = int(raw_input())
ans = 0
for i in range(1, n + 1):
    ans = ans + fac(i)
print ans
