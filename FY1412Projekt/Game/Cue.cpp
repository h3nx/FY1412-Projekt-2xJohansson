#include "Cue.h"



Cue::Cue()
{
}


Cue::~Cue()
{
}

void Cue::update()
{

}

void Cue::setMass(float mass)
{
	this->mass = mass;
}

void Cue::setFriction(float friction)
{
	this->friction = friction;
}

float Cue::getMass()
{
	return this->mass;
}

float Cue::getFriction()
{
	return this->friction;
}
