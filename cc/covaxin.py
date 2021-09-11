
I = int(input())
x, a, b, c, d = [int(i) for i in input().split()]
p, q, r, s, t, m = [int(i) for i in input().split()]
ans = 0
A = 0
B = 0
C = 0
inf = 1e18
PP = 0
x *= 2

def f(i):
    return (A * i + B) * i

def gao(n):
    global B
    global C
    B = PP - 2 * n * d
    C = n * (2 * c + (n - 1) * d)

    ans = inf
    xx = 0 - B // (2 * A)
    if xx < -5:
        ans = 0
    elif xx > n + 5:
        ans = f(n)
    else:
        ans = min(ans, f(xx))
        if xx - 1 >= 0 and xx - 1 <= n:
            ans = min(ans, f(xx - 1))
        if xx + 1 >= 0 and xx + 1 <= n:
            ans = min(ans, f(xx + 1))
    return ans + C

def solve():
    global A
    global PP
    PP = 2 * a - b - (2 * c - d)
    A = b + d
    l = 0
    r = int(3e9)
    ans = 0
    while l <= r:
        mid = (l + r) // 2
        tmp = gao(mid)
        if tmp <= x:
            ans = mid
            l = mid + 1
        else:
            r = mid - 1
    return int(ans)

for i in range(I):
    ans = solve()
    print(ans)
    a = (a + ans * t) % m + p
    b = (b + ans * t) % m + q
    c = (c + ans * t) % m + r
    d = (d + ans * t) % m + s
