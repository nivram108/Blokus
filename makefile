.PHONY: clean
all: test
test: main.o play.o ai.o game.o shapes.o
	g++ main.o play.o ai.o game.o shapes.o -o test
main.o: main.cpp play.cpp play.h play.o
	g++ main.cpp -c
play.o: play.cpp play.h ai.cpp ai.h game.cpp game.h shapes.cpp shapes.h
	g++ play.cpp -c
ai.o: ai.cpp ai.h game.cpp game.h shapes.cpp shapes.h
	g++ ai.cpp -c
game.o: game.cpp game.h shapes.cpp shapes.h
	g++ game.cpp -c
shapes.o: shapes.cpp shapes.h
	g++ shapes.cpp -c
clean:
	rm -rf main.o play.o ai.o game.o shapes.o
