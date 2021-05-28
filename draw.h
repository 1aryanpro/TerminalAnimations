#include <curses.h>

namespace draw {
	void init();
	void getScreenSize(int *sh, int *sw);
	WINDOW* createWin(int h, int w);
	void puts(float y, float x, char c);
	void draw();
	void end();
}
