TARGET=othello
CC=g++
OPT=-Wall -g -Wno-deprecated
INC=
LIB=-lglut -lGLU -lGL                 #Linux
#LIB=-framework OpenGL -framework GLUT #Mac
-include makefile.opt
.SUFFIXES:.cc .c .o .h

SRC=$(shell ls *.cc)
HED=$(shell ls *.h)
OBJ=$(SRC:.cc=.o)

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(OPT) -o $(TARGET) $(OBJ) $(LIB)
.cc.o:
	$(CC) $(OPT) -c $< $(INC)
dep:
	g++ -MM -MG $(SRC) >makefile.depend
clean:
	rm -f $(TARGET) $(TARGET).exe
	rm -f *.o *.obj
	rm -f *~ *.~*
-include makefile.depend
