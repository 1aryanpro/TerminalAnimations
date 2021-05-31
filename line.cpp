#include "draw.h"
#include <cmath>

#define PI 3.14159265

int main()
{
	int xMax = 100, yMax = 100;
	int ww, wh;
	float fps = 60, dt = 1 / fps;
	draw::init(fps);

	WINDOW *win = draw::createScaledWin(yMax, xMax, &wh, &ww);

	float theta = 0;
	float period = 2;
	float x, y;
	float px = xMax / 2, py = yMax / 2;
	
	int radius = 25;

	while (true)
	{
		int loopCount = draw::loopStart();

		for (int loopStep = 0; loopStep < loopCount; loopStep++)
		{
			theta += 2*PI/period * dt;
			x = px + cos(theta) * radius;
			y = py + sin(theta) * radius;
		}

		draw::line(py, px, y, x, '#');
		draw::puts(py, px, 'o');
		draw::puts(y, x, '@');
		draw::loopEnd();
	}

	draw::close();
}
