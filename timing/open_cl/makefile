#all:
#	gcc rsac.c -o rsac -lm

EXE = rsac
SRC = rsac.c
OBJ = rsac.o

LDLIBS = -lm

CFLAG = -std=c99 -Wall -fPIC
LDFLAG = -pie -fPIE

all: $(EXE)

$(EXE): $(OBJ)
	../Toolchain/bin/arm-linux-androideabi-gcc -o $@ $(LDFLAG) $^ -fPIE -lm

$(OBJ): $(SRC)
	../Toolchain/bin/arm-linux-androideabi-gcc -o $@ $(CFLAG) -c $<

clean:
	rm -fr $(EXE) $(OBJ)
