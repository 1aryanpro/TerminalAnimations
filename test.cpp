#include <iostream>
#include <cstdio>
#include <curses.h>

#include "draw.h"

int main()
{

	int xMax = 100, yMax = 100;
	int sw, sh;
	int ww, wh;
	float fps = 60, dt = 1 / fps;
	draw::init(fps);

	draw::getScreenSize(&sh, &sw);

	WINDOW *win = draw::createScaledWin(yMax, xMax, &wh, &ww);

	float x = xMax / 2, y = yMax / 2, dx = 15, dy = 0;

	while (true)
	{
		int loopCount = draw::loopStart();

		mvprintw(0, 0, "Window: %d x %d", ww, wh);
		mvprintw(1, 0, "Screen: %d x %d", sw, sh);
		mvprintw(0, 30, "pos: %f, %f", x, y);
		mvprintw(1, 30, "vel: %f, %f", dx, dy);

		for (int loopStep = 0; loopStep < loopCount; loopStep++)
		{
			x += dx * dt;
			y += dy * dt;
			dy += 0.1;

			if (x > xMax)
			{
				x = xMax;
				dx *= -1;
			}
			else if (x < 0)
			{
				x = 0;
				dx *= -1;
			}

			if (y > yMax)
			{
				y = yMax;
				dy *= -1;
			}
			else if (y < 0)
			{
				y = 0;
				dy *= -1;
			}
		}

		draw::puts(y, x, 'o');
		draw::loopEnd();
	}

	draw::close();

	return 0;
}
