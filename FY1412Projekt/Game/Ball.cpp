#include "Ball.h"

Ball::Ball()
{
	this->setPosition(Eigen::Vector3f(0, 0, 0));
	this->radius = 0.01;
	this->mass = 0;
	this->friction = 0;
	this->current_status = STOP;
}
Ball::Ball(Eigen::Vector3f position, float radius, float mass, float friction):Ball()
{
	this->setPosition(position);
	this->radius = radius;
	this->r2 = pow(radius, 2);
	this->mass = mass;
	this->friction = friction;

}
Ball::~Ball()
{
}

void Ball::update(float delta)
{
	if (current_status == SLIDE && this->getVelocity().norm() <= this->getRotationVelocity().norm() * radius_BALL)
		this->startRoll();
	
	

	if (this->getVelocity().norm() <= this->getAcceleration().norm() * delta) {
		this->setAcceleration(Eigen::Vector3f(0, 0, 0));
		this->setVelocity(Eigen::Vector3f(0, 0, 0));
	}
	this->move(delta);
	//this->rotate(delta);

}
void Ball::hit(Eigen::Vector3f vec_ball_cue, Eigen::Vector2f vec_hit_pos, float t_on_ball, float spring_k)
{	
	this->setVelocity(vec_ball_cue * spring_k * t_on_ball * (1 / mass_BALL));

	float z = sqrt(pow(vec_hit_pos[1], 2) + pow(radius_BALL, 2));
	Eigen::Vector3f N(vec_hit_pos[0], vec_hit_pos[1], z);

	

	
	//from friction in travel direction
	this->setAcceleration(vec_ball_cue.normalized() * u_BALL_CLOTH_SLIDE * g_ * -1);		//deacceleration
	this->setRotationAcceleration(Eigen::Vector3f(u_BALL_CLOTH_SLIDE * g_ / (0.4 * radius_BALL), 0, 0));	//rotation (perpendicular to friction)

	current_status = SLIDE;
}

void Ball::hit(Eigen::Vector3f vel_cue, Eigen::Vector3f hit_pos)
{
	Eigen::Vector3f ep = (this->getPosition() - hit_pos).normalized();
	Eigen::Matrix3f m;
	m << 0, 1, 0,
		-1, 0, 0,
		 0, 0, 1;
	

	Eigen::Vector3f en = m * ep;
	float Vcp = vel_cue.dot(ep);
	float Ubp = (1 + e_CUE_BALL)*mass_CUE * Vcp / (mass_BALL + mass_CUE);
		
	this->setVelocity(Ubp*(ep + /*u_ball_cue*/en));

	//this->setVelocity(vel_cue * (1 + e_CUE_BALL)* mass_CUE / (mass_BALL + mass_CUE));

	

	//from friction in travel direction
	this->setAcceleration(vel_cue.normalized() * u_BALL_CLOTH_SLIDE * g_ * -1);		//deacceleration
	this->setRotationAcceleration(vel_cue.normalized().cross(Eigen::Vector3f(0, 0, 1)) * u_BALL_CLOTH_SLIDE * g_ / (0.4 * radius_BALL));	//rotation (perpendicular to friction)

	current_status = SLIDE;
}

void Ball::setRadius(float radius)
{
	this->radius = radius;
	this->r2 = pow(radius, 2);
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
float Ball::getR2()
{
	return this->r2;
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
	current_status = ROLL;

	this->setAcceleration(this->getAcceleration().normalized() * u_BALL_CLOTH_ROLL * g_);
	this->setRotationAcceleration(u_BALL_CLOTH_ROLL * this->getRotationAcceleration() / u_BALL_CLOTH_SLIDE);
	
	//this->setVelocity(Eigen::Vector3f(0, 0, 0));
	//this->setAcceleration(Eigen::Vector3f(0, 0, 0));

}

