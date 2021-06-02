#include "draw.h"
#include <cmath>

#define PI 3.14159265

int main()
{
	int xMax = 100, yMax = 100;
	int ww, wh;
	float fps = 300, dt = 1 / fps;
	draw::init(fps);

	WINDOW *win = draw::createScaledWin(yMax, xMax, &wh, &ww);

	float ap = PI/4;
	float av = 0;

	float px = xMax / 2, py = yMax / 2;
	
	int radius = 45;

	while (true)
	{
		int loopCount = draw::loopStart();

		float x, y;
		for (int loopStep = 0; loopStep < loopCount; loopStep++)
		{
			float aa = sin(PI/2 - ap) / radius * dt;
			av += aa;
			ap += av;
		}

		x = px + cos(ap) * radius;
		y = py + sin(ap) * radius;

		draw::line(py, px, y, x, '#');
		draw::puts(py - 1, px, 'o');
		draw::puts(y, x, '@');
		draw::loopEnd();
	}

	draw::close();
}
