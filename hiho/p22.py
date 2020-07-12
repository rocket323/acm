
def solve():
    cnt = 0
    for i in range(2, n + 1):
        if r[a[i - 1] + 1] < r[a[i] + 1]:
            cnt = cnt + 1

    ans = 0
    for i in range(cnt, -1, -1):
        xx = n - i
        if xx > 26:
            break
        ans = ans + c[cnt][cnt - i] * c[26][xx]

    print ans

c = []
for i in range(0, 100010):
    c.append([0 for j in range(0, 28)])
    c[i][0] = 1
    for j in range(1, 28):
        if (j <= i):
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1]

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

