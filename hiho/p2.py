
def solve():
    f = [[0 for j in xrange(0, 26)] for i in xrange(0, 2)]
    for i in range(0, 26):
        f[0][i] = 1

    s = [0 for i in xrange(0, 26)]
    idx = 0

    for i in range(2, n + 1):
        idx = idx ^ 1
        s[0] = f[idx ^ 1][0]
        for j in range(1, 26):
            s[j] = s[j - 1] + f[idx ^ 1][j]

        for j in range(0, 26):
            f[idx][j] = 0
            if j > 0:
                f[idx][j] = s[j - 1]

            if r[a[i - 1] + 1] < r[a[i] + 1]:
                f[idx][j] = f[idx][j] + f[idx ^ 1][j]

    ans = 0
    for i in range(0, 26):
        ans = ans + f[idx][i]

    print ans

t = int(raw_input())
while t > 0:
    a = [0]
    n = int(raw_input())
    r = [0 for i in xrange(0, n + 10)]
    for x in raw_input().split():
        a.append(int(x))

    for i in range(1, len(a)):
        r[a[i]] = i

    t = t - 1
    solve()

