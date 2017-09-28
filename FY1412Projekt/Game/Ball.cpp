#include "Ball.h"



Ball::Ball()
{
	this->setPosition(Eigen::Vector3f(0, 0, 0));
	this->radius = 0;
	this->mass = 0;
	this->friction = 0;
}

Ball::Ball(Eigen::Vector3f position, float radius, float mass, float friction):Ball()
{
	this->setPosition(position);
	this->radius = radius;
	this->mass = mass;
	this->friction = friction;

}


Ball::~Ball()
{
}



void Ball::update()
{
	this->move();

}
















void Ball::setRadius(float radius)
{
	this->radius = radius;
}

void Ball::setMass(float mass)
{
	this->mass = mass;
}

void Ball::setFriction(float friction)
{
	this->friction = friction;
}

float Ball::getRadius()
{
	return this->radius;
}

float Ball::getMass()
{
	return this->mass;
}

float Ball::getFriction()
{
	return this->friction;
}
