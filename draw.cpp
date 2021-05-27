#include <iostream>
#include <curses.h>

namespace draw {
	void init() {
		initscr();
		noecho();
		curs_set(0);
	}

	void end() {
		endwin();
	}
}

//int main() {

//	draw::init();
//getch();
//draw::end();

// return 0;
//}
