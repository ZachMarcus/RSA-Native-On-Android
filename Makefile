EXE = rsaandroid
SRC = rsaandroid.c
OBJ = rsaandroid.o

CLROOT= Dependencies/

LDLIBS = -lm

CFLAG = -std=c99 -Wall -fPIC
LDFLAG = -pie -fPIE
INC = -I$(CLROOT)
LIB = -L$(CLROOT)lib/ -lOpenCL

all: $(EXE)

$(EXE): $(OBJ)
	Toolchain/bin/arm-linux-androideabi-gcc -o $@ $(LDFLAG) $^ $(LIB) -fPIE -lm

$(OBJ): $(SRC)
	Toolchain/bin/arm-linux-androideabi-gcc -o $@ $(CFLAG) $(INC) -c $<

clean:
	rm -fr $(EXE) $(OBJ)






