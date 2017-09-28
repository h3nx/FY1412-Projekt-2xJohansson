#pragma once
#include "..\FrameWork\Actor.h"
class Cue :
	public Actor
{
public:
	Cue();
	~Cue();
	void update();


private:
	float mass;
	float friction;
	



};

