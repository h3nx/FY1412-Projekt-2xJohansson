#include "Actor.h"



Actor::Actor()
{
	this->position = Vector3f(400, 400, 0);
	this->direction = Vector3f(0, 0, 0);
	this->velocity = Vector3f(0, 0, 0);
	this->acceleration = Vector3f(0, 0, 0);
	this->rotationVelocity = Vector3f(0, 0, 0);
	this->rotationAcceleration = Vector3f(0, 0, 0);
	this->scale = Vector3f(1, 1, 1);
	this->rotation = Vector3f(0, 0, 0);
	
}

Actor::Actor(Vector3f position):Actor()
{
	this->position = position;
}


Actor::Actor(Vector3f position, Vector3f rotation) :Actor(position)
{
	this->rotation = rotation;
}

Actor::~Actor()
{
}

void Actor::setPosition(Vector3f position)
{
	this->position = position;
}

void Actor::setDirection(Vector3f direction)
{
	this->direction = direction;
}

void Actor::setRotation(Vector3f rotation)
{
	this->rotationVelocity = rotation;
}

void Actor::setScale(Vector3f scale)
{
	this->scale = scale;
}

void Actor::setVelocity(Vector3f velocity)
{
	this->velocity = velocity;
}

void Actor::setAcceleration(Vector3f acceleration)
{
	this->acceleration = acceleration;
}

void Actor::setRotationVelocity(Vector3f rotVel)
{
	this->rotationVelocity = rotVel;
}

void Actor::setRotationAcceleration(Vector3f rotAcc)
{
	this->rotationAcceleration = rotAcc;
}



void Actor::changeVelocity(Vector3f delta)
{
	this->velocity += delta;
}

void Actor::changeRotationVelocity(Vector3f delta)
{
	this->rotationVelocity += delta;
}
void Actor::setSize(Vector3f size)
{
	this->size = size;
}
Vector3f Actor::getSize()
{
	return this->size;
}

void Actor::addHitbox(Vector3f position, float radius)
{
	
}

void Actor::addHitBox(Vector3f position, Vector3f sides)
{
}



bool Actor::collision(Actor & other)
{
	return false;
}

Vector3f Actor::getPosition()
{
	return this->position;
}

Vector3f Actor::getRotation()
{
	return this->rotation;
}
Vector3f Actor::getScale()
{
	return this->scale;
}

Vector3f Actor::getVelocity()
{
	return this->velocity;
}

Vector3f Actor::getAcceleration()
{
	return this->acceleration;
}

Vector3f Actor::getRotationVelocity()
{
	return this->rotationVelocity;
}



void Actor::update()
{
	this->move();
	this->rotate();
}

void Actor::move()
{
	this->velocity += this->acceleration;
	this->position += this->velocity;
	
	this->rotationVelocity += this->rotationAcceleration;
	this->rotation += this->rotationVelocity;


}
void Actor::rotate()
{
/*	this->rotation += this->rotationVelocity;
	for (int i = 0; i < 3; i++)
	{
		if (this->rotation[i] < 0)
			this->rotation[i] += 360;
		else if (this->rotation[i] > 359)
			this->rotation[i] -= 360;
	}
	*/
}


