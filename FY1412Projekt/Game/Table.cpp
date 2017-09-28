#include "Table.h"



Table::Table()
{
	this->balls = new Ball[15];
	


	for (int i = 0; i < 14; i++)
	{
		this->balls[i].setPosition(Eigen::Vector3f(i*0.05, i*0.05, 0));
	//	this->balls[i].setMass();
	
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
	for (int i = 0; i < 15; i++)
	{

	}


}



