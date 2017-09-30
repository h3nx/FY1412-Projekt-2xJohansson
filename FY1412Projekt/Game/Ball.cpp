#include "Ball.h"



Ball::Ball()
{
	this->setPosition(Eigen::Vector3f(0, 0, 0));
	this->radius = 0;
	this->mass = 0;
	this->friction = 0;
	this->isRolling = 0;
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



void Ball::update(float delta)
{
	if (!isRolling && this->getVelocity().norm() <= this->getRotationVelocity().norm() * radius_BALL)
		this->startRoll();
	
	this->move(delta);

	if (this->getVelocity().norm() <= this->getAcceleration().norm() * delta) {
		this->setAcceleration(Eigen::Vector3f(0, 0, 0));
		this->setVelocity(Eigen::Vector3f(0, 0, 0));
	}
	//this->rotate(delta);

}


void Ball::hit(Eigen::Vector3f vec_ball_cue, float t_on_ball, float spring_k)
{
	
	this->setVelocity(vec_ball_cue * spring_k * t_on_ball * (1 / mass_BALL));

	this->setAcceleration(vec_ball_cue.normalized() * u_BALL_CLOTH_SLIDE * g_ * -1);

	this->setRotationAcceleration(vec_ball_cue.normalized() * (u_BALL_CLOTH_SLIDE * g_ / (0.4 * radius_BALL)));
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

void Ball::startRoll()
{
	this->isRolling = true;

	this->setAcceleration(this->getAcceleration().normalized() * u_BALL_CLOTH_ROLL * g_);
	this->setRotationAcceleration(u_BALL_CLOTH_ROLL * this->getRotationAcceleration() / u_BALL_CLOTH_SLIDE);
	
	//this->setVelocity(Eigen::Vector3f(0, 0, 0));
	//this->setAcceleration(Eigen::Vector3f(0, 0, 0));

}

