#include "Timer.h"


Timer::Timer()
{
	this->startTime = GetTickCount();
	this->lastTime = GetTickCount();
	this->smoothing = 0.95;
	this->avg = 0;
}
Timer::Timer(const float smoothing):Timer()
{
	this->smoothing = smoothing;
}
Timer::~Timer()
{
}

float Timer::reset()
{
	this->startTime = GetTickCount();
	this->lastTime = GetTickCount();
	return 0;
}

float Timer::getTime()
{
	return difftime(GetTickCount(), startTime);
}


float Timer::deltaTime()
{
	float t = difftime(GetTickCount(), this->lastTime);
	this->lastTime = GetTickCount();
	
	this->avg = (this->avg * this->smoothing) + (t * (1 - this->smoothing));
	return t*0.001;
}

float Timer::getFPS()
{
	return 1000/this->avg;
}

float Timer::getAvg()
{
	return this->avg;
}
