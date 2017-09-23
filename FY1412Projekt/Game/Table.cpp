#include "Table.h"



Table::Table()
{
	this->ball = new Actor(Vector4f(200, 200, 0, 0));

	this->ball_shape.setFillColor(sf::Color(100, 250, 50));
	this->ball_shape.setPosition(0, 0);
	this->ball_shape.setRadius(radius_BALL / PIXEL_SIZE);

	this->shoot(0, Vector4f(1, 0, 0, 0), Vector4f(0.5, 0.5, 0, 0));
}


Table::~Table()
{
	delete this->ball;
}

void Table::update(float dt)
{
	Vector4f vel = this->ball->getVelocity(), acc = this->ball->getAcceleration() * dt;
	
	if (acc != Vector4f(0, 0, 0, 0))
	{
		vel(0) = (vel(0) <= acc(0)) ? (0, acc(0) = 0) : vel(0) + acc(0);
		vel(1) = (vel(1) <= acc(1)) ? (0, acc(1) = 0) : vel(1) + acc(1);
		vel(2) = (vel(2) <= acc(2)) ? (0, acc(2) = 0) : vel(2) + acc(2);
				
		this->ball->setVelocity(vel);
		this->ball->setAcceleration(acc / dt);

	}
	this->ball->update();
	
}

sf::CircleShape * Table::getBall()
{
	this->updateShapes();

	return &ball_shape;
}

void Table::shoot(int ballID, Vector4f velocity, Vector4f hitPos)
{
	this->ball->setVelocity(velocity);

	float acc = u_BALL_CLOTH_ROLL * u_BALL_CLOTH_ROLL * mass_BALL;

	this->ball->setAcceleration(Vector4f(acc * -1.0, 0, 0, 0));
}

void Table::updateShapes()
{
	Vector4f pos = this->ball->getPosition();
	this->ball_shape.setPosition(pos(0), pos(1)); 
}
