GFLAGS = -g -Wall
CC = g++
OBJMODULES = str.o Exception.o RationalNumber.o Graph.o GUI_back.o GUI_front.o
#HEADERS = Matrix.h Vector.h excep.h Exception.h str.h
SRCDIR = ../src/
HEADDIR = ../MT/
.PHONY: all, clear

##################################################
%.o: $(SRCDIR)%.cpp $(HEADDIR)%.h
	$(CC) $(CFLAGS) -c $< -o $@

Exception.o: str.o

excep.h: Exception.o

Vector = $(SRCDIR)Vector.cpp $(HEADDIR)excep.h

Matrix = Vector.o $(SRCDIR)Matrix.cpp $(HEADDIR)excep.h

RationaNumber.o: str.o $(HEADDIR)excep.h

Graph.o: $(HEADDIR)FLH

GUI_back.o: Graph.o RationalNumber.o $(HEADDIR)TwoL/TwoL.h $(HEADDIR)parameters.h $(HEADDIR)FLH $(Marix) $(Vector)

GUI_front.o: Graph.o GUI_back.o $(HEADDIR)TwoL/TwoL.h $(HEADDIR)parameters.h $(HEADDIR)FLH

calc: calc.cpp $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -lfltk 
	

all: 
	make $(OBJMODULES) -B

clear:
	rm *.o *~ a.out 


