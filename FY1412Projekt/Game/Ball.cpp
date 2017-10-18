#include "Ball.h"
#include "../sfmlRender/sfmlGraphics.h"
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
	Eigen::Vector2f w2 = this->getRotationVelocity().head<2>().dot(this->getVelocity().head<2>()) * this->getVelocity().head<2>().normalized();
	Eigen::Vector2f w1 = this->getRotationVelocity().head<2>() - w2;
	//float aa = atan2(w1, this->getRotationVelocity().head<2>());
	//float a = Eigen::Vector2f(1, 0).dot(this->getVelocity().head<2>().normalized());
	
	float a = atan2(this->getVelocity()[1], this->getVelocity()[0]);
	AngleAxis<float> rot(a, Eigen::Vector3f(0, 0, 1));
	Eigen::Vector3f wrot = rot * this->getRotationVelocity();

	Eigen::Vector3f potato, vp, faq;
	vp = this->getVelocity() - wrot[0] * radius_BALL * Eigen::Vector3f(0, 1, 0) - wrot[1] * radius_BALL*Eigen::Vector3f(1, 0, 0);

	potato = this->getVelocity() + this->getRotationVelocity().cross(Eigen::Vector3f(0, this->getRadius(), 0));

	if (this->getID() == 0)
		int blubb = 0;

	Eigen::Vector3f ff, aa;

	//perimeter velocity
	std::setprecision(2);
	vp = this->getRotationVelocity().cross(Eigen::Vector3f(0, 0, -this->radius)) + this->getVelocity();
	float potttt = this->getRotationVelocity().norm() * radius_BALL;
	float pointVel = vp.norm(); 
	if (this->getID() == 0)
	this->bullshit = 
		"rotVelrad: "+to_string(potttt) + " \n" + 
		"pointRot: "+to_string(pointVel)+"\n"+ 
		to_string(abs(pointVel - potttt)) + "\n" + 
		to_string(current_status)+"\n" +
		+"\n"  ;
	if(current_status == SLIDE && abs(pointVel - potttt) <= 0.1)
		this->startRoll();
	else if(current_status == SLIDE)
	{
		//from friction in travel direction
		Eigen::Vector3f af = vp.normalized() * u_BALL_CLOTH_SLIDE * -_g;
		//from rotation + friction
		this->setAcceleration(af - u_BALL_CLOTH_SLIDE * 9.82 * vp.normalized());



		//set rotation acc
		aa = Eigen::Vector3f(0,0,1).cross(-vp.normalized()) * u_BALL_CLOTH_SLIDE * _g / (0.4 * radius_BALL);
		if (this->getRotationVelocity()[2] > 0)
			aa[2] = -a_rota_BALL_CLOTH;
		else if (this->getRotationVelocity()[2] < 0)
			aa[2] = a_rota_BALL_CLOTH;
		else if (this->getRotationVelocity()[2] == 0)
			aa[2] = 0;
		this->setRotationAcceleration(aa);
	}
	//stop ball
	if (this->getVelocity().norm() <= this->getAcceleration().norm() * delta) {
		this->setAcceleration(Eigen::Vector3f(0, 0, 0));
		this->setVelocity(Eigen::Vector3f(0, 0, 0));
		this->setRotationVelocity(Eigen::Vector3f(0, 0, 0));
		this->setRotationAcceleration(Eigen::Vector3f(0, 0, 0));
	}
	//update vel + pos
	this->move(delta);
	this->rotate(delta);

	if (this->getVelocity().norm() == 0)
		current_status = STOP;

}




void Ball::hit(Eigen::Vector3f vel_cue, Eigen::Vector2f hit_pos)
{
	Eigen::Vector3f ep, en, ev, u, va, vp;
	//float _u = u_BALL_CLOTH_SLIDE;
	//vel_cue[2] = 0.3;
	

	// träff på bollen
	float hit_pos_x = sqrt(pow(radius_BALL, 2) - pow(hit_pos[0], 2) - pow(hit_pos[1], 2));
	ep = Eigen::Vector3f(hit_pos_x, hit_pos[0], hit_pos[1]).normalized();

	// bollens hastighet
	Eigen::Vector3f v = (1 + e_CUE_BALL)*mass_CUE * vel_cue / (mass_BALL + mass_CUE);
	this->setVelocity(v);
	
	//rotera punkten
	ep = AngleAxis<float>(atan2(v[1], v[0]), Eigen::Vector3f(0, 0, 1)) * ep;
	
	// rotations hastigheten och riktning
	float spinVel = (u_BALL_CUE * v.norm() / (0.4 * radius_BALL));
	u = vel_cue.normalized();
	en = (u - (u.dot(ep)*ep));
	Eigen::Vector3f eSpin = (ep.cross(en)) * spinVel;
	this->setRotationVelocity(eSpin);

	//perimeter velocity
	vp = eSpin.cross(Eigen::Vector3f(0, 0, -this->radius)) + v;
	//from friction in travel direction
	Eigen::Vector3f af = v.normalized() * u_BALL_CLOTH_SLIDE * -_g;
	//from rotation + friction
	this->setAcceleration(af - u_BALL_CLOTH_SLIDE * 9.82 * vp.normalized());


	/*


	float a = atan2(v[1], v[0]);
	AngleAxis<float> rot(a, Eigen::Vector3f(0, 0, 1));
	Eigen::Vector3f wrot = rot * this->getRotationVelocity();
	float w1 = wrot.head<2>().dot(Eigen::Vector2f(0, 1));
*/
	//if (hit_pos[1] <= 2 * radius_BALL / 5) {
	//	_u = u_BALL_CLOTH_ROLL;
	//	current_status = ROLL;
	//	this->setRotationVelocity(Eigen::Vector3f(0,0,0));
	//}
	//else {
	//	_u = u_BALL_CLOTH_SLIDE;
	//	current_status = SLIDE;
	//}
	//Eigen::Vector3f vp = v - eSpin[0] * radius_BALL * Eigen::Vector3f(0, 1, 0) - eSpin[1] * radius_BALL*Eigen::Vector3f(1, 0, 0);

	Eigen::Vector3f a_rota = v.normalized().cross(Eigen::Vector3f(0, 0, -1)) * u_BALL_CLOTH_SLIDE * _g / (0.4 * radius_BALL);

	if (eSpin[2] > 0)
		a_rota[2] = -a_rota_BALL_CLOTH;
	else if (eSpin[2] < 0)
		a_rota[2] = a_rota_BALL_CLOTH;
	else if (eSpin[2] == 0)
		a_rota[2] = 0;
	this->setRotationAcceleration(a_rota);
	
	current_status = SLIDE;	
	float potttt = this->getRotationVelocity().norm() * radius_BALL;
	float pointVel = vp.norm();
	if (this->getID() == 0)
		this->bullshit =
		"rotVelrad: " + to_string(potttt) + " \n" +
		"pointRot: " + to_string(pointVel) + "\n" +
		"diff: "+to_string(abs(pointVel - potttt)) + "\n" +
		to_string(current_status) + "\n" +
		+"\n";
	if (current_status == SLIDE && abs(pointVel - potttt) <= 0.1)
		this->startRoll();
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
	this->current_status = ROLL;
	this->setAcceleration(this->getVelocity().normalized() * u_BALL_CLOTH_ROLL * _g  * -1);		
	this->setRotationVelocity(Eigen::Vector3f(0, 0, 0));
	this->setRotationAcceleration(Eigen::Vector3f(0, 0, 0));


}


