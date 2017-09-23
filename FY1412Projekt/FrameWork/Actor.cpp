#include "Actor.h"



Actor::Actor()
{
	this->position = Vector4f(400, 400, 0, 1);
	this->direction = Vector4f(0, 0, 0, 0);
	this->velocity = Vector4f(0, 0, 0, 0);
	this->acceleration = Vector4f(0, 0, 0, 0);
	this->rotationVelocity = Vector4f(0, 0, 0, 0);
	this->rotationAcceleration = Vector4f(0, 0, 0, 0);
	this->scale = Vector4f(1, 1, 1, 0);
	this->rotation = Vector4f(0, 0, 0, 0);
	//this->hb = new Hitbox(0);
}

Actor::Actor(Vector4f position):Actor()
{
	this->position = position;
}


Actor::Actor(Vector4f position, Vector4f rotation) :Actor(position)
{
	this->rotation = rotation;
}

Actor::~Actor()
{
}

void Actor::setPosition(Vector4f position)
{
	this->position = position;
}

void Actor::setDirection(Vector4f direction)
{
	this->direction = direction;
}

void Actor::setRotation(Vector4f rotation)
{
	this->rotationVelocity = rotation;
}

void Actor::setScale(Vector4f scale)
{
	this->scale = scale;
}

void Actor::setVelocity(Vector4f velocity)
{
	this->velocity = velocity;
}

void Actor::setAcceleration(Vector4f acceleration)
{
	this->acceleration = acceleration;
}

void Actor::setRotationVelocity(Vector4f rotVel)
{
	this->rotationVelocity = rotVel;
}

void Actor::setRotationAcceleration(Vector4f rotAcc)
{
	this->rotationAcceleration = rotAcc;
}



void Actor::changeVelocity(Vector4f delta)
{
	this->velocity += delta;
}

void Actor::changeRotationVelocity(Vector4f delta)
{
	this->rotationVelocity += delta;
}
void Actor::setSize(Vector4f size)
{
	this->size = size;
}
Vector4f Actor::getSize()
{
	return this->size;
}

void Actor::addHitbox(Vector4f position, float radius)
{
	//this->hb->addHitbox(position, radius);
}

void Actor::addHitBox(Vector4f position, Vector4f sides)
{
}

void Actor::addHitBox(Vector4f position, Vector4f sides, Vector4f direction)
{
}

bool Actor::collision(Actor & other)
{
	return false;
}

Vector4f Actor::getPosition()
{
	return this->position;
}

Vector4f Actor::getRotation()
{
	return this->rotation;
}
Vector4f Actor::getScale()
{
	return this->scale;
}

Vector4f Actor::getVelocity()
{
	return this->velocity;
}

Vector4f Actor::getAcceleration()
{
	return this->acceleration;
}

Vector4f Actor::getRotationVelocity()
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
	this->position += this->velocity;

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


