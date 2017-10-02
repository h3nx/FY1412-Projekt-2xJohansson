#pragma once

#include "../FrameWork/Actor.h"
#include "Ball.h"
#include "Cue.h"
#include "SFML\Graphics.hpp"
#include "../FrameWork/Timer.h"

using namespace Eigen;

//#define u_BALL_CLOTH_SLIDE 0.2f
//#define u_BALL_CLOTH_ROLL 0.01f
#define mass_BALL 0.165f //kg
//#define radius_BALL 0.0286f

#define PIXEL_SIZE 0.002767f/4.0f // 16:9 24" 1920*1080
#define TABLESIZE_X 2.6
#define TABLESIZE_Y TABLESIZE_X*0.5;


class Table
{
public:
	Table();
	~Table();

	void update(float dt);

	Actor* getBall(unsigned int id);
	Actor* getCue();
	void beginShot();
	void endShot(Eigen::Vector3f mPos);
	float shotTime;

private:
	Ball* balls;
	Cue* cue;
	int shooting;
	Timer* time;


	float pixelSize;
private:


	void shoot(int ballID, Eigen::Vector3f velocity, Eigen::Vector3f hitPos);
	void updateActors(float dt);


};

