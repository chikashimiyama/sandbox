to compile shared lib
cc -shared test.c -o libtest.so

to use library
cc -I ./ -L ./ test.c  -o test -lmymath
