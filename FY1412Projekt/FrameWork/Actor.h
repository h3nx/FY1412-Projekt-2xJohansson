#pragma once
#ifndef Actoraaa_H
#define Actoraaa_H
#include "../Eigen/Core"
//#include "Hitbox.h"
//#include <../Eigen/Eigen>
//#include <../Eigen/Geometry>
using namespace Eigen;

class Actor
{

public:
	Actor();
	Actor(Vector4f position);
	Actor(Vector4f position, Vector4f rotation);
	~Actor();


	void setPosition(Vector4f position);
	void setDirection(Vector4f direction);
	void setRotation(Vector4f rotation);
	void setScale(Vector4f scale);
	void setVelocity(Vector4f velocity);
	void setAcceleration(Vector4f acceleration);
	void setRotationVelocity(Vector4f rotVel);
	void setRotationAcceleration(Vector4f rotAcc);
	void setSize(Vector4f size);
	
	void changeVelocity(Vector4f delta);
	void changeRotationVelocity(Vector4f delta);

	void addHitbox(Vector4f position, float radius);
	void addHitBox(Vector4f position, Vector4f sides);
	void addHitBox(Vector4f position, Vector4f sides, Vector4f direction);

//	void removeHitbox(Vector4f position);

	bool collision(Actor& other);


	Vector4f getPosition();
	Vector4f getRotation();  //?
	Vector4f getScale();
	Vector4f getVelocity();
	Vector4f getAcceleration();
	Vector4f getRotationVelocity();
	//Vector4f getRotationAcceleration();
	Vector4f getSize();

	void update();

private:
	Vector4f position;
	Vector4f direction;
	Vector4f scale;
	Vector4f velocity;
	Vector4f acceleration;
	Vector4f rotation;	// rotation har v�l bara velocity + acceleration?
	Vector4f rotationVelocity;
	Vector4f rotationAcceleration;
	Vector4f size;
	//Hitbox* hb;

	

private:
	Matrix4f worldMatrix();
	void move();
	void rotate();
};



#endif