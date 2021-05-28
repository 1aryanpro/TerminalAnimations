draw: draw.cpp draw.h
	g++ draw.cpp -std=c++14 -lncurses -pthread -o draw.out

test: draw.cpp draw.h test.cpp
	g++ draw.cpp test.cpp -std=c++14 -lncurses -pthread -o test.out


