TARGET=othello
CC=g++
OPT=-Wall -g
INC=
LIB=-lglut -lGLU -lGL
-include makefile.opt
.SUFFIXES:.cpp .hpp .c .o .h

SRC=$(shell ls *.cpp)
HED=$(shell ls *.hpp)
OBJ=$(SRC:.cpp=.o)

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(OPT) -o $(TARGET) $(OBJ) $(LIB)
.cpp.o:
	$(CC) $(OPT) -c $< $(INC)
dep:
	g++ -MM -MG $(SRC) >makefile.depend
clean:
	rm -f $(TARGET) $(TARGET).exe
	rm -f *.o *.obj
	rm -f *~ *.~*
-include makefile.depend
