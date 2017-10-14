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
	if (current_status == SLIDE && this->getVelocity().norm() <= this->getRotationVelocity().head<2>().norm() * radius_BALL)
		this->startRoll();
	
	

	if (this->getVelocity().norm() <= this->getAcceleration().norm() * delta) {
		this->setAcceleration(Eigen::Vector3f(0, 0, 0));
		this->setVelocity(Eigen::Vector3f(0, 0, 0));
	}
	this->move(delta);
	this->rotate(delta);

	if (this->getVelocity().norm() == 0)
		current_status = STOP;

}
void Ball::hit(Eigen::Vector3f vec_ball_cue, Eigen::Vector2f vec_hit_pos, float t_on_ball, float spring_k)
{	
	this->setVelocity(vec_ball_cue * spring_k * t_on_ball * (1 / mass_BALL));

	float z = sqrt(pow(vec_hit_pos[1], 2) + pow(radius_BALL, 2));
	Eigen::Vector3f N(vec_hit_pos[0], vec_hit_pos[1], z);

	

	
	//from friction in travel direction
	this->setAcceleration(vec_ball_cue.normalized() * u_BALL_CLOTH_SLIDE * _g * -1);		//deacceleration
	this->setRotationAcceleration(Eigen::Vector3f(u_BALL_CLOTH_SLIDE * _g / (0.4 * radius_BALL), 0, 0));	//rotation (perpendicular to friction)

	current_status = SLIDE;
}

void Ball::hit(Eigen::Vector3f vel_cue, Eigen::Vector2f hit_pos)
{
	/*Eigen::Vector3f ep = (this->getPosition() - hit_pos).normalized();
	Eigen::Matrix3f m;
	m << 0, 1, 0,
		-1, 0, 0,
		 0, 0, 1;
	

	Eigen::Vector3f en = m * ep;
	float Vcp = vel_cue.dot(ep);
	float Ubp = (1 + e_CUE_BALL)*mass_CUE * Vcp / (mass_BALL + mass_CUE);
		
	this->setVelocity(Ubp*(ep + u_BALL_CUE*en));*/
	Eigen::Vector3f v = (1 + e_CUE_BALL)*mass_CUE * vel_cue / (mass_BALL + mass_CUE);
	this->setVelocity(v);
		
	float w;
	w = (hit_pos[0] * mass_CUE * vel_cue.norm()) / (0.4 * mass_BALL * radius_BALL *  radius_BALL);
	this->setRotationVelocity(Eigen::Vector3f(0, 0, w));

	//from friction in travel direction
	float _u;
	if (hit_pos[1] >= 2 * radius_BALL / 5) {
		_u = u_BALL_CLOTH_ROLL;
		current_status = ROLL;
	}
	else {
		_u = u_BALL_CLOTH_SLIDE;
		current_status = SLIDE;
	}

	this->setAcceleration(v.normalized() * _u * _g * -1);		//deacceleration
	Eigen::Vector3f a_rota = v.normalized().cross(Eigen::Vector3f(0, 0, 1)) * _u * _g / (0.4 * radius_BALL);
	a_rota[2] = a_rota_BALL_CLOTH;//a_rota.head<2>().norm();
	this->setRotationAcceleration(a_rota);



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

	//this->setAcceleration(this->getAcceleration().normalized() * u_BALL_CLOTH_ROLL * g_);


	this->setAcceleration(this->getVelocity().normalized() * u_BALL_CLOTH_ROLL * _g * -1);	
	Eigen::Vector3f a_rota = this->getVelocity().normalized().normalized().cross(Eigen::Vector3f(0, 0, 1)) * u_BALL_CLOTH_ROLL * _g / (0.4 * radius_BALL);
	a_rota[2] = a_rota_BALL_CLOTH;// a_rota.head<2>().norm();
	this->setRotationAcceleration(a_rota);
	
	//this->setVelocity(Eigen::Vector3f(0, 0, 0));
	//this->setAcceleration(Eigen::Vector3f(0, 0, 0));

}

