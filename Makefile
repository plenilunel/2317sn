all : main

main: main.cpp src/GameManager.hpp src/Board.hpp src/Misc.hpp src/snake.hpp
	g++ main.cpp -lncurses -o main