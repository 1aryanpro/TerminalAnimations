#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "draw.h"

typedef struct {
	int x;
	int y;
} Vector;

namespace vector
{
	Vector *make(int x, int y)
	{
		Vector* out = (Vector*)malloc(sizeof(Vector));
		out->x = x;
		out->y = y;

		return out;
	}
}

int main()
{

	int xMax = 100, yMax = 100;
	int sw, sh;
	int ww, wh;
	float fps = 60, dt = 1 / fps;
	draw::init(fps);

	draw::getScreenSize(&sh, &sw);

	WINDOW *win = draw::createScaledWin(yMax, xMax, &wh, &ww);

	float x = xMax / 2, y = yMax / 4, dx = 10, dy = 0;

	size_t trail_len = 100;
	Vector *trail[trail_len];

	for (size_t i = 0; i < trail_len; i++)
	{
		trail[i] = vector::make(0, 0);
	}


	while (true)
	{
		int loopCount = draw::loopStart();

		int sx, sy;
		draw::getScreenCoords(y, x, &sy, &sx);

		mvprintw(0, 0, "Window:     %d x %d", ww, wh);
		mvprintw(1, 0, "Screen:     %d x %d", sw, sh);
		mvprintw(2, 0, "Screen Pos: %d x %d", sx, sy);
		mvprintw(0, 30, "pos: %f, %f", x, y);
		mvprintw(1, 30, "vel: %f, %f", dx, dy);


		if (loopCount > 0) 
		{
			for (size_t i = 0; i < trail_len - 1; i++)
			{
				trail[i]->x = trail[i+1]->x;	
				trail[i]->y = trail[i+1]->y;	
			}
			trail[trail_len-1] = vector::make(sx, sy);
		}

		for (size_t i = 0; i < trail_len - 1; i++)
		{
			Vector *cur = trail[i];
			if(i > trail_len / 2) { draw::sputs(cur->y, cur->x, ':'); }
			else { draw::sputs(cur->y, cur->x, '.'); }
		}


		for (int loopStep = 0; loopStep < loopCount; loopStep++)
		{
			x += dx * dt;
			y += dy * dt;
			dy += 0.2;

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
				dy *= -0.95;
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
