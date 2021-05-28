#include <curses.h>

namespace draw {
	void init();
	WINDOW* createWin(int h, int w);
	void puts(float y, float x, char c);
	void draw();
	void end();
}
