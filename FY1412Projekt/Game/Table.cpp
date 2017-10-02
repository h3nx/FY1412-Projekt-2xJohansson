#include "Table.h"



Table::Table()
{
	this->balls = new Ball[15];
	this->time = new Timer();
	this->cue = new Cue();
	this->pixelSize =  (2.6 / (1920*0.9));
	this->shooting = 0;
	this->shotTime = 0;



	// ball init
	for (int i = 0; i < 15; i++)
	{
		this->balls[i].setPosition(Eigen::Vector3f(i*0.05, i*0.05, 0));
		this->balls[i].setMass(mass_BALL);
		this->balls[i].setVelocity(Eigen::Vector3f(0.01, 0, 0));
		this->balls[i].setAcceleration(Eigen::Vector3f(0, 0.00001, 0));
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


Table::~Table()
{
	delete[] this->balls;
	delete this->cue;
}

void Table::update(float dt)
{
	this->updateActors(dt);

	if (this->shooting)
	{


	}


}
  
Actor * Table::getBall(unsigned int id)
{
	return &this->balls[id];
}

Actor * Table::getCue()
{
	return this->cue;
}

void Table::updateCuePos(Eigen::Vector2f mPos)
{

	Eigen::Vector3f wPos = Eigen::Vector3f(mPos[0], mPos[1], 0)*this->pixelSize;
	Eigen::Vector3f relPos = (wPos - this->balls[0].getPosition()).normalized();

	float angle = 270+atan2(relPos[1], relPos[0])*(180/3.14);
	this->cue->setPosition(wPos+(relPos*this->shotTime));
	this->cue->setRotation(Eigen::Vector3f(0,0,angle));
	

}

void Table::beginShot()
{
	this->time->reset();
	this->shooting = 1;
}

void Table::endShot(Eigen::Vector3f mPos)
{

	float t = this->time->deltaTime()*3;
	this->shotTime = t;
	if (t > 4)
		t = 4;

	this->balls[0].hit((this->balls[0].getPosition()-mPos*this->pixelSize).normalized()*t, 0.01, 10);
	this->shotTime = 0;
	this->shooting = 0;
}

void Table::updateActors(float dt)
{
	for (int i = 0; i < 15; i++)
	{
		this->balls[i].update(dt);
	}
	if (this->shooting)
	{
		this->shotTime = this->time->getTime();
		//if (this->shotTime > 4)
		//	this->shotTime = 4;
	}
		

}



