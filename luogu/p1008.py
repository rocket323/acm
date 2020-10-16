
def check(n, bs):
    ns = str(n)
    for c in ns:
        if bs.has_key(c) or c == '0':
            return False
        bs[c] = 1
    return True

for n in range(123, 1000):
    bs = dict()
    if check(n, bs) and check(n * 2, bs) and check(n * 3, bs):
        print("%d %d %d" % (n, n * 2, n * 3))
