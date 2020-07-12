#/usr/bin/python

n = 17
a = n ** n
b = 1
for i in range(1, 18):
    print i
    b *= i
print a, b, a / b

