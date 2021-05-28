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


using namespace std;
int main() {

	int width = 54, height = 54;
	draw::init();

	WINDOW *win = draw::createWin(height, width);
	
	const float fps = 60.0f;
	const float dt = 1.0f/fps;
	float accumulator = 0.0f;
	Timer tmr;
	float frameStart = tmr.elapsed();

	float x = width/2, y = height/2, dx = 1, dy = 0;

	while(true) {
		float currentTime = tmr.elapsed();
		accumulator += currentTime - frameStart;

		frameStart=currentTime;
		printf("%d, %d", width, height);

		//if(accumulator >= 1.0f / 30.0f)	accumulator = 1.0f / 30.0f;

		while(accumulator > dt)
		{
			x += dx/10;
			y += dy/10;
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

