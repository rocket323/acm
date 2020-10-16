#!/usr/bin/python

def solve(a):
    f = [[0 for j in range(0, 100)] for i in range(0, 100)]
    for c in range(0, m):
        for l in range(0, c + 1):
            num1, num2 = a[l], a[m - (c - l) - 1]
            f[c+1][l+1] = max(f[c+1][l+1], f[c][l] + num1 * t[c+1])
            f[c+1][l] = max(f[c+1][l], f[c][l] + num2 * t[c+1])

    ans = 0
    for l in range(0, m + 1):
        ans = max(ans, f[m][l])
    return ans

if __name__ == "__main__":
    t = [1]
    for i in range(1, 100):
        t.append(t[-1] * 2)
    while True:
        try:
            n, m = list(map(int, raw_input().split()))
            a = list()
            for i in range(0, n):
                tmp = list(map(int, raw_input().split()))
                a.append(tmp)
            ans = 0
            for i in range(0, n):
                ans = ans + solve(a[i])
            print ans
        except EOFError:
            break

