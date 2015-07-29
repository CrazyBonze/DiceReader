sfml-app: main.o
	g++ -Wall -pedantic -g -o DiceReader main.o dicereader.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp dicereader.o
	g++ -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c main.cpp

dicereader.o: dicereader.cpp dicereader.h
	g++ -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c dicereader.cpp

clean:
	rm *.o DiceReader

run:
	./DiceReader
