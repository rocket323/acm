

g++ gen.cpp -o gen
./gen > test.in
g++ 2915.cpp
g++ 2915/6511767_AC_17438MS_2416K.cpp -o other
echo "my"
time ./a.out < test.in
echo "other"
time ./other < test.in