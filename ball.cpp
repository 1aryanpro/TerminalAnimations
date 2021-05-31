#include "draw.h"
#include "vector.h"


int main()
{

	int xMax = 100, yMax = 100;
	int sw, sh;
	int ww, wh;
	float fps = 60, dt = 1 / fps;
	draw::init(fps);

	draw::getScreenSize(&sh, &sw);

	WINDOW *win = draw::createScaledWin(yMax, xMax, &wh, &ww);

	Vector pos = vector::make(xMax / 2, yMax / 2);
	Vector vel = vector::make(10, 0);

	size_t trail_len = 10;
	Vector trail[trail_len];

	for (size_t i = 0; i < trail_len; i++)
	{
		trail[i] = vector::make(-1, -1);
	}


	while (true)
	{
		int loopCount = draw::loopStart();

		int sx, sy;
		draw::getScreenCoords(pos.y, pos.x, &sy, &sx);
		Vector screenPos = vector::make(sx, sy);

		mvprintw(0, 0, "Window:     %d x %d", ww, wh);
		mvprintw(1, 0, "Screen:     %d x %d", sw, sh);
		mvprintw(2, 0, "Screen Pos: %d x %d", sx, sy);
		mvprintw(0, 30, "pos: %f, %f", pos.x, pos.y);
		mvprintw(1, 30, "vel: %f, %f", vel.x, vel.y);


		if (loopCount > 0 && !vector::cmp(trail[trail_len-1], screenPos)) 
		{
			for (size_t i = 0; i < trail_len - 1; i++)
			{
				trail[i].x = trail[i+1].x;	
				trail[i].y = trail[i+1].y;	
			}
			trail[trail_len-1] = screenPos;
		}

		for (size_t i = 0; i < trail_len - 1; i++)
		{
			Vector cur = trail[i];
			if(i > trail_len / 2) { draw::sputs(cur.y, cur.x, ':'); }
			else { draw::sputs(cur.y, cur.x, '.'); }
		}


		for (int loopStep = 0; loopStep < loopCount; loopStep++)
		{
			Vector scaledVel = vector::mul(vel, dt);
			pos = vector::add(pos, scaledVel);
			vel.y += 9.81 * dt;

			if (pos.x > xMax)
			{
				pos.x = xMax;
				vel.x *= -1;
			}
			else if (pos.x < 0)
			{
				pos.x = 0;
				vel.x *= -1;
			}

			if (pos.y > yMax)
			{
				pos.y = yMax;
				vel.y *= -0.95;
			}
			else if (pos.y < 0)
			{
				pos.y = 0;
				vel.y *= -1;
			}

		}


		draw::puts(pos.y, pos.x, 'o');
		draw::loopEnd();
	}

	draw::close();

	return 0;
}
