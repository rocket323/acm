
def solve(n):
    a = list(bin(n)[2:])[::-1]
    idx = len(a) - 1
    ans = []
    while idx >= 0:
        if a[idx] == '0':
            idx = idx - 1
            continue
        if idx == 0:
            ans.append('2(0)')
        elif idx == 1:
            ans.append('2')
        else:
            ans.append('2(%s)' % solve(idx))
        idx = idx - 1
    return '+'.join(ans)

n = int(raw_input())
print solve(n)
