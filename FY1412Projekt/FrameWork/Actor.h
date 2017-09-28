#pragma once
#ifndef Actoraaa_H
#define Actoraaa_H
#include "../Eigen/Core"

using namespace Eigen;

class Actor
{

public:
	Actor();
	Actor(Vector3f position);
	Actor(Vector3f position, Vector3f rotation);
	~Actor();

	virtual void update() = 0;
	void setPosition(Vector3f position);
	void setDirection(Vector3f direction);
	void setRotation(Vector3f rotation);
	void setScale(Vector3f scale);
	void setVelocity(Vector3f velocity);
	void setAcceleration(Vector3f acceleration);
	void setRotationVelocity(Vector3f rotVel);
	void setRotationAcceleration(Vector3f rotAcc);
	void setSize(Vector3f size);
	
	void changeVelocity(Vector3f delta);
	void changeRotationVelocity(Vector3f delta);

	void addHitbox(Vector3f position, float radius);
	void addHitBox(Vector3f position, Vector3f sides);

	bool collision(Actor& other);


	Vector3f getPosition();
	Vector3f getRotation();  
	Vector3f getScale();
	Vector3f getVelocity();
	Vector3f getAcceleration();
	Vector3f getRotationVelocity();
	Vector3f getRotationAcceleration();
	Vector3f getSize();


private:
	Vector3f position;
	Vector3f direction;
	Vector3f scale;
	Vector3f velocity;
	Vector3f acceleration;
	Vector3f rotation;	
	Vector3f rotationVelocity;
	Vector3f rotationAcceleration;
	Vector3f size;
	//Hitbox* hb;

	

private:
	Matrix4f worldMatrix();
	
protected:
	void move();
	void rotate();
	
};



#endif