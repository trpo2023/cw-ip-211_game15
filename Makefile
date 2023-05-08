all:
	g++ -Isrc/include -c main.cpp
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
.PHONY: clean run

run: 
	./main

clean:
	rm -r main.o
	rm -r main.exe