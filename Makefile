GMP=$(HOME)/Desktop/Projects/Math/gmp_install

all: test

test: test.c
	cc -I$(GMP)/include -L$(GMP)/lib -lgmp test.c  -o test
run:
	./test > res.txt
clean:
	rm -f test