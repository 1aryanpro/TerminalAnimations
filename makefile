ball: draw.cpp draw.h timer.h vector.h ball.cpp
	g++ draw.cpp ball.cpp -std=c++14 -lncurses -pthread -o ball.out

line: draw.cpp draw.h timer.h vector.h line.cpp
	g++ draw.cpp line.cpp -std=c++14 -lncurses -pthread -o line.out

