#pragma once
#ifndef Actoraaa_H
#define Actoraaa_H
//#include "../Eigen/Core"
#include "../Eigen/Dense"
#include "../Eigen/Geometry"
using namespace Eigen;

class Actor
{

public:
	Actor();
	Actor(Eigen::Vector3f position);
	Actor(Eigen::Vector3f position, Eigen::Vector3f rotation);
	~Actor();

	virtual void update(float delta);
	void setPosition(Eigen::Vector3f position);
	void setDirection(Eigen::Vector3f direction);
	void setRotation(Eigen::Vector3f rotation);
	void setScale(Eigen::Vector3f scale);
	void setVelocity(Eigen::Vector3f velocity);
	void setAcceleration(Eigen::Vector3f acceleration);
	void setRotationVelocity(Eigen::Vector3f rotVel);
	void setRotationAcceleration(Eigen::Vector3f rotAcc);
	void setSize(Eigen::Vector3f size);
	void setID(unsigned int id);

	void changeVelocity(Eigen::Vector3f delta);
	void changeRotationVelocity(Eigen::Vector3f delta);

	void addHitbox(Eigen::Vector3f position, float radius);
	void addHitBox(Eigen::Vector3f position, Eigen::Vector3f sides);

	bool collision(Actor& other);


	Eigen::Vector3f getPosition();
	Eigen::Vector3f getRotation();  
	Eigen::Vector3f getScale();
	Eigen::Vector3f getVelocity();
	Eigen::Vector3f getAcceleration();
	Eigen::Vector3f getRotationVelocity();
	Eigen::Vector3f getRotationAcceleration();
	Eigen::Vector3f getSize();
	unsigned int getID();


private:
	Eigen::Vector3f position;
	Eigen::Vector3f direction;
	Eigen::Vector3f scale;
	Eigen::Vector3f velocity;
	Eigen::Vector3f acceleration;
	Eigen::Vector3f rotation;	
	Eigen::Vector3f rotationVelocity;
	Eigen::Vector3f rotationAcceleration;
	Eigen::Vector3f size;
	unsigned int id;
private:


protected:
	void move(float delta);
	void rotate(float delta);
	
};



#endif