#pragma once
#include "..\FrameWork\Actor.h"

#define u_BALL_CLOTH_SLIDE 0.2f
#define u_BALL_CLOTH_ROLL 0.01f
#define mass_BALL 0.165f //kg
#define radius_BALL 0.0286f
#define g_ 9.82f



class Ball :
	public Actor
{
public:
	Ball();
	Ball(Eigen::Vector3f position, float radius, float mass, float friction);
	~Ball();

	void update(float delta);

	void hit(Eigen::Vector3f vec_ball_cue, float t_on_ball, float k_spring);

	void setRadius(float radius);
	void setMass(float mass);
	void setFriction(float friction);

	float getRadius();
	float getMass();
	float getFriction();


private:
	bool isRolling;
	float radius;
	float mass;
	float friction;

	void startRoll();

};

