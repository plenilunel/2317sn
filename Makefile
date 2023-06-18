all : main

main: main.cpp src/GameManager.hpp src/Misc.hpp src/snake.hpp src/Board.hpp src/Spawner.hpp src/ScoreBoard.hpp src/Stage.hpp
	g++ main.cpp -lncurses -o main