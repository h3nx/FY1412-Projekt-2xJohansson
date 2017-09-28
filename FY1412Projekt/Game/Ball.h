#pragma once
#include "..\FrameWork\Actor.h"
class Ball :
	public Actor
{
public:
	Ball();
	Ball(Eigen::Vector3f position, float radius, float mass, float friction);
	~Ball();

	void update();


	void setRadius(float radius);
	void setMass(float mass);
	void setFriction(float friction);

	float getRadius();
	float getMass();
	float getFriction();

private:
	float radius;
	float mass;
	float friction;

};

