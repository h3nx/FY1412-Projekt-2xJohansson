#pragma once

#include "../FrameWork/Actor.h"
#include "Ball.h"
#include "Cue.h"
#include "Table.h"
#include "SFML\Graphics.hpp"
#include "../FrameWork/Timer.h"
#include "../Eigen/Geometry"

using namespace Eigen;

//#define u_BALL_CLOTH_SLIDE 0.2f
//#define u_BALL_CLOTH_ROLL 0.01f
#define mass_BALL 0.165f //kg
#define radius_BALL 0.0286f

#define PIXEL_SIZE 0.002767f/4.0f // 16:9 24" 1920*1080
#define TABLESIZE_X 2.6
#define TABLESIZE_Y TABLESIZE_X*0.5;

typedef enum shootingStatus { RELEASING = -1, WAITING, DRAWING, HOLDING};


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
	void setScreenSize(unsigned int x, unsigned int y);
	Eigen::Vector3f drawBackDir;
	Eigen::Vector3f drawBack;

	void setBalls();

	Eigen::Vector2f ballHit;
	Eigen::Vector3f mPos;

private:
	Ball* balls;
	Cue* cue;
	Table* table;
	
	int shooting;
	Timer* time;

	float shotTime;
	Eigen::Vector3f shotVec;

	float pixelSize;
	bool inMotion;
	

private:


	void shoot(int ballID, Eigen::Vector3f velocity, Eigen::Vector3f hitPos);
	void updateActors(float dt);
	void cueAnimation(float dt);
	void collisionTest(float dt);

	bool collision(unsigned int id1, unsigned int id2, float delta);
	bool collision(int ballId);
	void holeTest(int ballId);

};

