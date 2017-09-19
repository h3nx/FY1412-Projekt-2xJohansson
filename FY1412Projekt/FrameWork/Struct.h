#pragma once
#ifndef RandomShit
#define RandomShit

#include <Windows.h>
#include <string>
#include "../Eigen/Core"
struct vec
{
	float x = 0;
	float y = 0;

	vec()
	{
		this->x = 0;
		this->y = 0;
	};
	vec(int x, int y)
	{
		this->x = x;
		this->y = y;
	};


};




#endif


