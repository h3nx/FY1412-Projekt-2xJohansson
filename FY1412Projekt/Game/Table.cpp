#include "Table.h"



Table::Table()
{
	this->balls = new Ball[15];
	


	for (int i = 0; i < 15; i++)
	{
		this->balls[i].setPosition(Eigen::Vector3f(i*0.05, i*0.05, 0));
		this->balls[i].setMass(mass_BALL);
		this->balls[i].setVelocity(Eigen::Vector3f(0.01, 0, 0));
		this->balls[i].setAcceleration(Eigen::Vector3f(0, 0.00001, 0));
		this->balls[i].setID(i);
	}


	this->cue = new Cue();
}


Table::~Table()
{
	delete[] this->balls;
	delete this->cue;
}

void Table::update(float dt)
{
	this->updateActors(dt);


}

Actor * Table::getBall(unsigned int id)
{
	return &this->balls[id];
}

Actor * Table::getCue()
{
	return this->cue;
}

void Table::beginShot()
{

}

void Table::endShot()
{

}

void Table::updateActors(float dt)
{
	for (int i = 0; i < 15; i++)
	{
		this->balls[i].update(dt);
	}



}



