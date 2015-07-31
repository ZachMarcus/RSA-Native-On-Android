EXE = rsaandroid
SRC = rsaandroid.c
OBJ = rsaandroid.o

CLROOT= /home/zachary/RSANativeOnAndroid/THEPROJECT/importantIncludes/
TOOLCHAINROOT = /home/zachary/RSANativeOnAndroid/UpdatedToolchain/bin/

LDLIBS = -lm

CFLAG = -std=c99 -Wall -fPIC
LDFLAG = -pie -fPIE
INC = -I$(CLROOT)
LIB = -L$(CLROOT)lib/ -lOpenCL

all: $(EXE)

$(EXE): $(OBJ)
	/home/zachary/RSANativeOnAndroid/UpdatedToolchain/bin/arm-linux-androideabi-gcc -o $@ $(LDFLAG) $^ $(LIB) -fPIE -lm

$(OBJ): $(SRC)
	/home/zachary/RSANativeOnAndroid/UpdatedToolchain/bin/arm-linux-androideabi-gcc -o $@ $(CFLAG) $(INC) -c $<

clean:
	rm -fr $(EXE) $(OBJ)






