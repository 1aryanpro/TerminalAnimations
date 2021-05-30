#include <iostream>
#include <chrono>
#include <curses.h>
#include "timer.h"

Timer::Timer() : beg_(clock_::now()) {}
void Timer::reset() { beg_ = clock_::now(); }
float Timer::elapsed()
{
	return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
}

int roundDown(int number, int multiple)
{
	int result = ((number + multiple / 2) / multiple) * multiple;
	return result;
}

namespace draw
{
	WINDOW *win;
	int height, width;
	int yMax, xMax;
	int windowHeight, windowWidth;
	Timer tmr;
	float fps, dt;
	float accumulator, frameStart;

	void init(float _fps)
	{
		initscr();
		noecho();
		curs_set(0);

		getmaxyx(stdscr, height, width);

		fps = _fps;
		dt = 1.0f / fps;
		accumulator = 0.0f;
		frameStart = tmr.elapsed();
	}

	void getScreenSize(int *_sh, int *_sw)
	{
		*_sh = height;
		*_sw = width;
	}

	WINDOW *createWin(int h, int w)
	{
		int wh = (h * 8 / 18);
		int ww = w;

		win = newwin(wh + 2, ww + 2, (height - wh) / 2 - 1, (width - ww) / 2 - 1);
		return win;
	}

	WINDOW *createScaledWin(float _yMax, float _xMax, int *_wh, int *_ww)
	{
		float xyratio = _xMax / _yMax;
		float yxratio = _yMax / _xMax;

		if (width >= height * 18 / 8 * yxratio)
		{
			windowHeight = roundDown(height * 0.75 * yxratio, 8) * 18 / 8;
			windowWidth = windowHeight * xyratio;
		}
		else
		{
			windowWidth = roundDown(width * 0.75 * xyratio, 18);
			windowHeight = windowWidth * yxratio;
		}

		*_wh = windowHeight;
		*_ww = windowWidth;
		yMax = _yMax;
		xMax = _xMax;

		return createWin(windowHeight, windowWidth);
	}

	void puts(float y, float x, char c)
	{
		int sy = y / yMax * windowHeight;
		int sx = x / xMax * windowWidth;
		mvwaddch(win, sy * 8 / 18 + 1, sx + 1, c);
	}

	int loopStart()
	{
		float currentTime = tmr.elapsed();
		accumulator += currentTime - frameStart;
		frameStart = currentTime;

		if (accumulator >= 1.0f / 30.0f)
			accumulator = 1.0f / 30.0f;

		int count = 0;

		while (accumulator >= dt)
		{
			count++;
			accumulator -= dt;
		}

		return count;
	}

	void loopEnd()
	{
		box(win, 0, 0);
		wrefresh(win);
		refresh();
		werase(win);
	}

	void close()
	{
		endwin();
	}
}
