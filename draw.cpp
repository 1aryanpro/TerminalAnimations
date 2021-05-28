#include <iostream>
#include <curses.h>

namespace draw {
	WINDOW *win;
	int height;
	int width;

	void init() {
		initscr();
		noecho();
		curs_set(0);

		getmaxyx(stdscr, height, width);
	}

	void getScreenSize(int *sh, int *sw) {
		*sh = height;
		*sw = width;
	}

	WINDOW *createWin(int h, int w) {
		int wh = (h*8/18);
		int ww = w;

		win = newwin(wh + 2, ww + 2, (height - wh)/2 - 1, (width - ww) / 2 - 1); 
		return win;
	}

	void puts(float y, float x, char c) {
		mvwaddch(win, y*8/18+1, x+1, c);
	}

	void draw() {
		box(win, 0, 0);
		wrefresh(win);
		refresh();
		werase(win);
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
