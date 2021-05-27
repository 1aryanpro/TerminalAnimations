draw: draw.cpp
	g++ draw.cpp -std=c++14 -lncurses -pthread -o draw.out

test: draw.cpp test.cpp
	g++ draw.cpp test.cpp -std=c++14 -lncurses -pthread -o test.out


