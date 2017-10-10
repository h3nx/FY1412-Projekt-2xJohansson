#include "Pool.h"



Pool::Pool()
{
	this->balls = new Ball[15];
	this->time = new Timer();
	this->cue = new Cue();
	this->pixelSize =  (2.6 / (1920*0.9));
	this->shooting = 0;
	this->shotTime = 0;
	this->ballHit = Eigen::Vector2f(0, 0);


	// ball init
	for (int i = 0; i < 15; i++)
	{
		this->balls[i].setPosition(Eigen::Vector3f(i*0.05, i*0.05, 0));
		this->balls[i].setMass(mass_BALL);
		this->balls[i].setVelocity(Eigen::Vector3f(0.01, 0, 0));
		this->balls[i].setAcceleration(Eigen::Vector3f(0, 0.00001, 0));
		this->balls[i].setRadius(0.0286);
		this->balls[i].setID(i);
	}


	//tmp whiteball
	this->balls[0].setPosition(Eigen::Vector3f(1, 1, 0));
	this->balls[0].setVelocity(Eigen::Vector3f(0, 0, 0));
	this->balls[0].setAcceleration(Eigen::Vector3f(0, 0, 0));

	this->cue->setPosition(Eigen::Vector3f(1, 1, 0));
	this->cue->setRotation(Eigen::Vector3f(0, 0, 0));
	this->cue->setID(15);

}
Pool::~Pool()
{
	delete[] this->balls;
	delete this->cue;
}

void Pool::update(float dt)
{
	
	this->updateActors(dt);



}
  
Actor * Pool::getBall(unsigned int id)
{
	return &this->balls[id];
}
Actor * Pool::getCue()
{
	return this->cue;
}

void Pool::updateCuePos(Eigen::Vector2f mPos)
{
	this->mPos = Eigen::Vector3f(mPos[0], mPos[1], 0)*this->pixelSize;


}
void Pool::beginShot()
{
	this->time->reset();
	this->shooting = 1;
	this->drawBackDir = (this->mPos-this->balls[0].getPosition()).normalized(); // Vec: mus till boll
	this->drawBack = this->drawBackDir*this->balls[0].getRadius() * 3;
}
void Pool::endShot(Eigen::Vector3f mPos)
{	
	this->shooting = -1;
	this->shotVec = drawBack;
}
void Pool::updateActors(float dt)
{
	//Balls
	for (int i = 0; i < 15; i++)
	{
		this->balls[i].update(dt);
	}
	//Cue
	this->cueAnimation(dt);

}

void Pool::cueAnimation(float dt)
{
	static float animationStep = 0;
	static int direction;
	Eigen::Vector3f relPos;
	float angle;
	

	if (this->shooting != WAITING)
	{
		if (this->shooting == DRAWING)
		{
			if(this->drawBack.squaredNorm() < pow(1,2))
			this->drawBack += this->drawBackDir * 0.75 * dt; // x * dt m/s
		}
		if (this->shooting == RELEASING)
		{
			this->drawBack += this->drawBackDir * -2 * dt; // x * dt m/s
			if (this->drawBack.squaredNorm() < this->balls[0].getR2())
			{
				this->balls[0].hit(-this->shotVec*2, this->ballHit, 0.1, 3);
				//Eigen::Vector3f p = this->balls[0].getPosition();
				//this->balls[0].hit(Eigen::Vector3f(1, 0, 0), Eigen::Vector3f(0, p[1] - 0.01, 0));
				this->shooting = WAITING;
				this->cue->setPosition(Eigen::Vector3f(-10,-10,0));
			}
		}
		angle = atan2(this->drawBackDir[1], this->drawBackDir[0])*(180 / 3.14159265359) - 90;
		this->cue->setPosition(this->balls[0].getPosition()+this->drawBack);
	}
	else
	{
		if (this->balls[0].getVelocity().squaredNorm() == 0)
		{
			relPos = (this->mPos - this->balls[0].getPosition()).normalized();
			this->cue->setPosition(this->balls[0].getPosition() + relPos*this->balls[0].getRadius()*3);
			angle = atan2(relPos[1], relPos[0])*(180 / 3.14159265359) - 90;
		}
		else
		{
			this->cue->setPosition(Eigen::Vector3f(-10,-10,-10));

		}

	}
	this->cue->setRotation(Eigen::Vector3f(0, 0, angle));





	/*					///// old version /////


	if (this->shooting == 1)
	{
		if (this->shotTime < 3)
		{
			

			this->shotTime = this->time->getTime() * 1;
			if (this->shotTime > 3)
				this->shotTime = 3;
		}
	}
	if (shooting == -1)
		relPos = (this->shotPos - this->balls[0].getPosition()).normalized();
	else
		relPos = (this->mPos - this->balls[0].getPosition()).normalized();

	float angle = atan2(relPos[1], relPos[0])*(180 / 3.14) - 90;
	this->cue->setRotation(Eigen::Vector3f(0, 0, angle));

	if (this->balls[0].getVelocity().squaredNorm() == 0)
		this->cue->setPosition(this->balls[0].getPosition() + (relPos*(this->shotTime + 0.1)));
	else
		this->cue->setPosition(Eigen::Vector3f(100, 100, 100));

	if (this->shooting)
	{
		if (this->shooting == 1)
		{
			animationStep = this->shotTime;


		}
		if (this->shooting == -1)
		{
			animationStep -= dt * 4;
			this->cue->setPosition(this->balls[0].getPosition() + (relPos*(animationStep)));

			if (animationStep < 0.05)
			{
				this->balls[0].hit(-relPos*this->shotTime, this->ballHit, 0.1, 10);
				this->shooting = 0;
				this->shotTime = 0;
			}

		}

	}
	else
		animationStep = 0.1;
		*/



}

void Pool::collisionTest()
{

	for (int i = 0; i < 7; i++)
	{
		// balls
		for (int u = 0; u < 15; u++)
		{
			//this->collision(i, u);


		}
		// table

	}
	

}

bool Pool::collision(unsigned int id1, unsigned int id2)
{
	static float PI = 3.14159265;
	static float rad = PI / 180;



	Eigen::Vector3f n = this->balls[id1].getPosition() - this->balls[id2].getPosition();
	float l2 = n.squaredNorm();
	float r2 = this->balls[id1].getRadius();
	if (l2 > r2)
		return false;
	
	Eigen::Vector3f v1(8, 0, 0);
	Eigen::Vector3f v2(0, 0, 0);
	float angle = 0 * rad;
	Eigen::Rotation2D<float> r(angle*rad);


	float m1 = 10, m2 = 5;
	float e = 0.9;
	float v1p = v1[0] * cos(angle) + v1[1] * sin(angle);
	float v1n = -v1[0] * sin(angle) + v1[1] * sin(angle);

	float v2p = v2[0] * cos(angle) + v2[1] * sin(angle);
	float v2n = -v2[0] * sin(angle) + v2[1] * sin(angle);

	float vv1p = ((m1 - e*m2) / (m1 + m2))*v1p;
	float vv2p = (((1 + e)*m1) / (m1 + m2))*v1p;

	float v1x = vv1p * cos(angle*rad) - v1n*sin(angle*rad);
	float v1y = vv1p * sin(angle*rad) + v1n*cos(angle*rad);
	float v2x = vv2p*cos(angle*rad) - v2n*sin(angle*rad);
	float v2y = vv2p*sin(angle*rad) + v2n*cos(angle*rad);

	Eigen::Vector2f v12(v1x, v1y);
	Eigen::Vector2f v22(v2x, v2y);



	return true;
}



