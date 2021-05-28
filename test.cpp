#include <iostream>
#include <cstdio>
#include <chrono>
#include "draw.h"
#include <curses.h>

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    float elapsed() const {
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration< float, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

int roundDown (int number, int multiple) {
	int result = ((number + multiple/2) / multiple) * multiple;
	return result;
}

int main() {

	int width, height;
	int sw, sh;
	draw::init();

	draw::getScreenSize(&sh, &sw);

  	if (sw >= sh * 18/8) {
  		height = roundDown(sh * 3/4, 8) * 18/8;
  		width = height;
  	} else {
  		width = sw - sw%8;
  		height = width;
  	}

	WINDOW *win = draw::createWin(width, height);
	
	const float fps = 60.0f;
	const float dt = 1.0f/fps;
	float accumulator = 0.0f;
	Timer tmr;
	float frameStart = tmr.elapsed();

	float x = 15, y = 15, dx = 5, dy = 0;

	while(true) {
		float currentTime = tmr.elapsed();
		accumulator += currentTime - frameStart;
		frameStart=currentTime;

		if(accumulator >= 1.0f / 30.0f)	accumulator = 1.0f / 30.0f;

		mvprintw(0, 0, "Window: %d x %d", width, height);
		mvprintw(1, 0, "Screen: %d x %d", sw, sh);
		mvprintw(0, 30, "pos: %f, %f", x, y);
		mvprintw(1, 30, "vel: %f, %f", dx, dy);

		while(accumulator > dt)
		{
			x += dx*dt;
			y += dy*dt;
			dy += 0.05;
			
			if(x > width){
				x = width;
				dx *= -1;
			} else if(x < 0){
				x = 0;
				dx *= -1;
			}

			if(y > height){
				y = height;
				dy *= -1;
			} else if(y < 0){
				y = 0;
				dy *= -1;
			}

			accumulator -= dt;
		}
		
		draw::puts(y, x, 'o');
		draw::draw();
	}

	draw::end();

	return 0;
}

