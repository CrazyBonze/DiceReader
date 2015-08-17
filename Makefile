DiceReader: main.o
	g++ -fstack-check -m64 -Wall -pedantic -g -o DiceReader main.o dicereader.o -lsfml-graphics

main.o: main.cpp dicereader.o
	g++ -fstack-check -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c main.cpp

dicereader.o: dicereader.cpp dicereader.h
	g++ -fstack-check -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c dicereader.cpp

clean:
	rm *.o DiceReader

run:
	./DiceReader dice.png

runp:
	./DiceReader -p dice.png
