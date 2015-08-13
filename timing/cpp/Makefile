#g++ unit.c -lgmpxx -lgmp
CC      = g++
CFLAGS  = 
LDFLAGS = -lgmpxx -lgmp

all: rsa-gmp clean

rsa-gmp: rsa-gmp.o
	$(CC) -o $@ $^ $(LDFLAGS)

rsa-gmp.o: rsa-gmp.c
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm rsa-gmp