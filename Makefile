all:bin
	g++ -Isrc/SFML/include -c src/game15/main.cpp -o obj/src/game15/main.o
	g++ obj/src/game15/main.o -o bin/main -Lsrc/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
.PHONY: clean run test

run: 
	./main

test:bin
	 g++ -Isrc/SFML/include -c test/test.cpp -o obj/test/main.o
	 g++ obj/test/main.o -o bin/test -Lsrc/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
	 ./bin/test


clean:
	rm -r main.o
	rm -r main.exe