EXE = rsacygwin 
SRC = rsacygwin.c
OBJ = rsacygwin.o

CLROOT = /opt/AMDAPPSDK-3.0-0-Beta/

#is this going to work, I don't know:
LDLIBS = -lm


CFLAG = -std=c99 -Wall
LDFLAG = 
INC = -I$(CLROOT)/include
LIB = -L$(CLROOT)/lib/x86_64 -lOpenCL

all: $(EXE)

$(EXE): $(OBJ)
	gcc -o $@ $(LDFLAG) $^ $(LIB) -lm

$(OBJ): $(SRC)
	gcc -o $@ $(CFLAG) $(INC) -c $<

clean:
	rm -fr $(EXE) $(OBJ)
