checkers.exe: main.o board.o
	g++ -std=c++11 -o checkers.exe main.o board.o

main.o: inc/game.h inc/main.h src/main.cpp src/board.o
	g++ -std=c++11 -c src/main.cpp

board.o: inc/colors.h inc/board.h inc/main.h inc/game.h src/board.cpp
	g++ -std=c++11 -c src/board.cpp


clean:
	crm -rf *.o checkers.exe *~