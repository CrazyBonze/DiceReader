DiceReader: main.o
	g++ -O3 -fstack-check -m64 -Wall -pedantic -g -o DiceReader main.o dicereader.o matrix.o -lsfml-graphics

main.o: main.cpp dicereader.o matrix.o
	g++ -O3 -fstack-check -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c main.cpp

dicereader.o: dicereader.cpp dicereader.h matrix.o
	g++ -O3 -fstack-check -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c dicereader.cpp

matrixTest: matrixTest.o
	g++ -O3 -fstack-check -m64 -Wall -pedantic -g -o matrixTest matrixTest.o matrix.o

matrixTest.o: matrixTest.cpp matrix.o
	g++ -O3 -fstack-check -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c matrixTest.cpp

matrix.o: matrix.cpp matrix.h
	g++ -O3 -fstack-check -m64 -g -std=c++11 -Wall -W -Werror -pedantic -c matrix.cpp

clean:
	rm *.o DiceReader matrixTest

run:
	./DiceReader dice.png

runp:
	./DiceReader -p dice.png
