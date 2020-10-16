L = int(raw_input())
n = int(raw_input())
if n == 0:
    print 0, 0
    exit(0)
a = map(int, raw_input().split())

ans1, ans2 = 0, 0
for p in a:
    d1 = p
    d2 = L + 1 - p
    if d1 > d2:
        d1, d2 = d2, d1
    if d1 > ans1: ans1 = d1
    if d2 > ans2: ans2 = d2

print ans1, ans2
