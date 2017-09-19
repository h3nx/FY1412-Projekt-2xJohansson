#pragma once
#ifndef TIMER_H
#define TIMER_H
#include <time.h>
#include <windows.h>



class Timer
{
public:
	Timer();

	Timer(const float smoothing);
	~Timer();
	float reset();
	float getTime();
	float deltaTime();
	float getFPS();
	float getAvg();

private:
	time_t startTime;
	time_t lastTime;
	float avg;
	float smoothing;

};




#endif