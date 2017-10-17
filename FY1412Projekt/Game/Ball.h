#pragma once
#include "..\FrameWork\Actor.h"

#define u_BALL_CLOTH_SLIDE 0.2f
#define u_BALL_CLOTH_ROLL 0.015f
#define u_BALL_CUE 0.9f
#define u_BALL_BALL 0.055f
#define mass_BALL 0.165f 
#define mass_CUE 0.540f 
#define radius_BALL 0.0286f
#define e_CUE_BALL 0.73
#define e_BALL_BALL 0.95
#define e_BALL_WALL 0.5
#define a_rota_BALL_CLOTH 10.f
#define _g 9.82f

typedef enum status{ STOP, SLIDE, ROLL };

class Ball :
	public Actor
{
public:
	Ball();
	Ball(Eigen::Vector3f position, float radius, float mass, float friction);
	~Ball();
	
	void update(float delta);

	void hit(Eigen::Vector3f vel_cue, Eigen::Vector2f hit_pos);

	void setRadius(float radius);
	void setMass(float mass);
	void setFriction(float friction);

	float getRadius();
	float getR2();
	float getMass();
	float getFriction();




private:
	status current_status;
	float radius;
	float r2;
	float mass;
	float friction;


private:
	void startRoll();

};

