#include "Actor.h"



Actor::Actor()
{
	this->position = Vector3f(0, 0, 0);
	this->direction = Vector3f(0, 0, 0);
	this->velocity = Vector3f(0, 0, 0);
	this->acceleration = Vector3f(0, 0, 0);
	this->rotationVelocity = Vector3f(0, 0, 0);
	this->rotationAcceleration = Vector3f(0, 0, 0);
	this->scale = Vector3f(1, 1, 1);
	this->rotation = Vector3f(0, 0, 0);
	this->id = 0;
}

Actor::Actor(Eigen::Vector3f position):Actor()
{
	this->position = position;
}


Actor::Actor(Eigen::Vector3f position, Eigen::Vector3f rotation) :Actor(position)
{
	this->rotation = rotation;
}

Actor::~Actor()
{
}

void Actor::setID(unsigned int id)
{
	this->id = id;
}
void Actor::setPosition(Eigen::Vector3f position)
{
	this->position = position;
}
void Actor::setDirection(Eigen::Vector3f direction)
{
	this->direction = direction;
}
void Actor::setRotation(Eigen::Vector3f rotation)
{
	this->rotation = rotation;
}
void Actor::setScale(Eigen::Vector3f scale)
{
	this->scale = scale;
}
void Actor::setSize(Eigen::Vector3f size)
{
	this->size = size;
}
void Actor::setVelocity(Eigen::Vector3f velocity)
{
	this->velocity = velocity;
}
void Actor::setAcceleration(Eigen::Vector3f acceleration)
{
	this->acceleration = acceleration;
}
void Actor::setRotationVelocity(Eigen::Vector3f rotVel)
{
	this->rotationVelocity = rotVel;
}
void Actor::setRotationAcceleration(Eigen::Vector3f rotAcc)
{
	this->rotationAcceleration = rotAcc;
}

void Actor::changeVelocity(Eigen::Vector3f delta)
{
	this->velocity += delta;
}
void Actor::changeRotationVelocity(Eigen::Vector3f delta)
{
	this->rotationVelocity += delta;
}



unsigned int Actor::getID()
{
	return this->id;
}
Eigen::Vector3f Actor::getPosition()
{
	return this->position;
}
Eigen::Vector3f Actor::getRotation()
{
	return this->rotation;
}
Eigen::Vector3f Actor::getScale()
{
	return this->scale;
}
Eigen::Vector3f Actor::getSize()
{
	return this->size;
}
Eigen::Vector3f Actor::getVelocity()
{
	return this->velocity;
}
Eigen::Vector3f Actor::getAcceleration()
{
	return this->acceleration;
}
Eigen::Vector3f Actor::getRotationVelocity()
{
	return this->rotationVelocity;
}
Eigen::Vector3f Actor::getRotationAcceleration()
{
	return this->rotationAcceleration;
}



void Actor::update(float delta)
{
	//this->move(delta);
	//this->rotate(delta);
}
void Actor::move(float delta)
{
	this->velocity += this->acceleration * delta;
	this->position += this->velocity * delta;
	
	//this->rotationVelocity += this->rotationAcceleration * delta;
	//this->rotation += this->rotationVelocity * delta;


}
void Actor::rotate(float delta	)
{	
	//z rotation will stop if hitting 0 or going between +/-
	if (this->rotationAcceleration[2] != 0) {
		float oldZ = this->rotationVelocity[2], newZ = oldZ + this->rotationAcceleration[2] * delta;
		if ((oldZ < 0 && newZ >= 0) ||
			(oldZ > 0 && newZ <= 0)) {
			this->rotationVelocity[2] = 0;
			this->rotationAcceleration[2] = 0;
		}
	}
	
	this->rotationVelocity += this->rotationAcceleration * delta;
	this->rotation += this->rotationVelocity * delta;
	
	for (int i = 0; i < 3; i++)
	{
		if (this->rotation[i] < 0)
			this->rotation[i] += 360;
		else if (this->rotation[i] > 359)
			this->rotation[i] -= 360;
	}
	
}


