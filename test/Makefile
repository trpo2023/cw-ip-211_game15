CC=g++
CFLAGS=-c -Wall
LIBS=-lm
INCLUDES=-I.
SRCDIR=.
TESTSDIR=.

all: game15_logic_test

game15_logic_test: $(TESTSDIR)/test.o 
	$(CC) $(TESTSDIR)/test.o  -o game15_logic_test $(LIBS)

$(TESTSDIR)/test.o: $(TESTSDIR)/test.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTSDIR)/test.cpp -o $(TESTSDIR)/test.o


test: $(SRCDIR)/game15_logic_test
	./game15_logic_test

clean:
	rm -f $(TESTSDIR)/*.o $(SRCDIR)/*.o game15_logic_test