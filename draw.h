#ifndef DRAW_H
#define DRAW_H

#include <curses.h>
#include "timer.h"

int roundDown(int number, int multiple);

namespace draw
{
	void init(float _fps);
	WINDOW *createWin(int h, int w);
	WINDOW *createScaledWin(float h, float w, int *_wh, int *_ww);
	void puts(float y, float x, char c);
	int loopStart();
	void loopEnd();
	void close();

	void getScreenSize(int *_sh, int *_sw);
}

#endif
