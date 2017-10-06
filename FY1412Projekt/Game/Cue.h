#pragma once
#include "..\FrameWork\Actor.h"
class Cue :
	public Actor
{
public:
	Cue();
	~Cue();
	void update();

	void setMass(float mass);
	void setFriction(float friction);

	float getMass();
	float getFriction();

private:
	float mass;
	float friction;
	



};

