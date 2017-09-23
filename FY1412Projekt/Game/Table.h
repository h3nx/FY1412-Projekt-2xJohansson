#pragma once

#include "../FrameWork/Actor.h"
#include "SFML\Graphics.hpp"

using namespace Eigen;

#define u_BALL_CLOTH_SLIDE 0.2f
#define u_BALL_CLOTH_ROLL 0.01f
#define mass_BALL 0.165f //kg
#define radius_BALL 0.0286f
#define PIXEL_SIZE 0.002767f // 16:9 24" 1920*1080

class Table
{
public:
	Table();
	~Table();

	void update(float dt);

	sf::CircleShape* getBall();


private:
	Actor* ball;
	sf::CircleShape ball_shape; //gör om till array


private:

	void shoot(int ballID, Vector4f velocity, Vector4f hitPos); // kommer nog behöva vara public

	void updateShapes();


};