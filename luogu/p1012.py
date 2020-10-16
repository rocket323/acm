
n = int(raw_input())
a = raw_input().split()

def cmp_func(a, b):
    s1 = a + b
    s2 = b + a
    if s1 > s2:
        return -1
    elif s1 == s2:
        return 0
    else:
        return 1

a.sort(cmp = cmp_func)
print ''.join(a)
