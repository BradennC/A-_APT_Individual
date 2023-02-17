.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Tile.o Node.cpp LinkedList.o qwirkle.o RulesEngine.o BoardLocation.o LinkedList.o GamesEngine.o Player.o TileBag.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
