#include <iostream>
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

int main() {

	draw::init();
	int mx, my;
	getmaxyx(stdscr, my, mx);

	WINDOW *win = newwin(my/2, mx/2, my/4, mx/4);
	box(win, 0, 0);
	
	const float fps = 60.0f;
	const float dt = 1.0f/fps;
	float accumulator = 0.0f;
	Timer tmr;
	float frameStart = tmr.elapsed();

	float x = mx/2, y = my/2, dx = 1, dy = 0;

	while(true) {
		float currentTime = tmr.elapsed();
		accumulator += currentTime - frameStart;

		frameStart=currentTime;


		//if(accumulator >= 1.0f / 30.0f)	accumulator = 1.0f / 30.0f;

		while(accumulator > dt)
		{
			x += dx/10;
			y += dy/10;
			dy += 0.05;
			
			if(x > mx){
				x = mx;
				dx *= -1;
			} else if(x < 0){
				x = 0;
				dx *= -1;
			}

			if(y > my){
				y = my;
				dy *= -1;
			} else if(y < 0){
				y = 0;
				dy *= -1;
			}

			accumulator -= dt;
		}
		
		werase(win);
		box(win, 0, 0);
		mvwaddch(win, y/2, x/2, 'o');
		wrefresh(win);

	}

	draw::end();

	return 0;
}

