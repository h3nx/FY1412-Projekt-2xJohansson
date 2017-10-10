#pragma once

#include "../FrameWork/Actor.h"
#include "Ball.h"
#include "Cue.h"
#include "Table.h"
#include "SFML\Graphics.hpp"
#include "../FrameWork/Timer.h"

using namespace Eigen;

//#define u_BALL_CLOTH_SLIDE 0.2f
//#define u_BALL_CLOTH_ROLL 0.01f
#define mass_BALL 0.165f //kg
#define radius_BALL 0.0286f

#define PIXEL_SIZE 0.002767f/4.0f // 16:9 24" 1920*1080
#define TABLESIZE_X 2.6
#define TABLESIZE_Y TABLESIZE_X*0.5;

typedef enum shootingStatus { RELEASING = -1, WAITING, DRAWING };


class Pool
{
public:
	Pool();
	~Pool();

	void update(float dt);

	Actor* getBall(unsigned int id);
	Actor* getCue();
	void updateCuePos(Eigen::Vector2f mPos);
	void beginShot();
	void endShot(Eigen::Vector3f mPos);
	Eigen::Vector3f drawBackDir;
	Eigen::Vector3f drawBack;

private:
	Ball* balls;
	Cue* cue;
	Table* table;
	
	int shooting;
	Timer* time;

	Eigen::Vector2f ballHit;
	float shotTime;
	Eigen::Vector3f mPos;
	Eigen::Vector3f shotVec;

	float pixelSize;

private:


	void shoot(int ballID, Eigen::Vector3f velocity, Eigen::Vector3f hitPos);
	void updateActors(float dt);
	void cueAnimation(float dt);
	void collisionTest();

	bool collision(Ball b1, Ball b2);
	bool collision(int ballId);

};

