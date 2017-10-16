#include "Pool.h"



Pool::Pool()
{
	this->balls = new Ball[15];
	this->time = new Timer();
	this->cue = new Cue();
	this->table = new Table();
	this->pixelSize =  (2.6 / (1920-100));
	this->shooting = 0;
	this->shotTime = 0;
	this->ballHit = Eigen::Vector2f(0, 0);


	this->table->setPosition(Eigen::Vector3f(1.3, 0.65, 0));
	this->table->setSize(Eigen::Vector3f(1.223, 0.573, 0));

	// ball init
	for (int i = 0; i < 15; i++)
	{
		
		this->balls[i].setMass(mass_BALL);
		this->balls[i].setRadius(0.0286);
		this->balls[i].setID(i);
	}

	this->setBalls();
	//tmp whiteball
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
	//this->collisionTest(dt);



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
	if (this->shooting == HOLDING && this->mPos[0] <= 2.6 && this->mPos[1] < 1.3)
	{
		for (int i = 1; i < 15; i++)
		{
			if (((this->balls[i].getPosition() - this->mPos).norm()) <= 2 * radius_BALL)
				return;
		}
		this->balls[0].setPosition(this->mPos);
	}

}
void Pool::beginShot()
{
	if (this->mPos[0] <= 2.6 && this->mPos[1] < 1.3)
	{
		if (this->shooting == WAITING)
		{
			this->time->reset();
			this->shooting = 1;
			this->drawBackDir = (this->mPos - this->balls[0].getPosition()).normalized(); // Vec: mus till boll
			this->drawBack = this->drawBackDir*this->balls[0].getRadius() * 3;
		}
		if (this->shooting == HOLDING)
		{
			this->shooting = WAITING;

		}
	
	}
	else if (this->mPos[0] > 2.6 && this->mPos[1] < 0.135)
	{
		Eigen::Vector2f pos(
			(this->mPos[0] - 2.6) / 2.3,
			this->mPos[1] / 2.3);
		pos -= Eigen::Vector2f(0.0286, 0.0286);
		if (pos.squaredNorm() < pow(0.0286, 2)) {
			this->ballHit = pos;
			this->ballHit[1] *= -1;
		}
	}
	
}
void Pool::endShot(Eigen::Vector3f mPos)
{	
	if (this->shooting)
	{
		this->shooting = -1;
		this->shotVec = drawBack;
	}
}
void Pool::setScreenSize(unsigned int x, unsigned int y)
{
	this->pixelSize = (2.6 / (x-100));
}
void Pool::setBalls()
{
	this->balls[0].setPosition(Eigen::Vector3f(0.5, 0.65, 0));
	for (int i = 1; i < 15; i++)
	{
		this->balls[i].setPosition(Eigen::Vector3f(i*0.1+0.3, 0.5, 0));
	}

}
void Pool::updateActors(float dt)
{
	//Balls
	for (int i = 0; i < 15; i++)
	{
		this->holeTest(i);
		this->balls[i].update(dt);
		this->collision(i);
		for (int u = 0; u < 15; u++)
			if (i != u)
				this->collision(i, u, dt);


	}
	//Cue
	this->cueAnimation(dt);


}

void Pool::cueAnimation(float dt)
{
	Eigen::Vector3f relPos;
	float angle;
	

	if (this->shooting != WAITING && this->shooting != HOLDING)
	{
		if (this->shooting == DRAWING)
		{
			if(this->drawBack.squaredNorm() < pow(0.5,2))
			this->drawBack += this->drawBackDir * 0.75 * dt; // x * dt m/s
		}
		if (this->shooting == RELEASING)
		{
			this->drawBack += this->drawBackDir *( this->shotVec.norm()*4 * -dt); // x * dt m/s
			if (this->drawBack.squaredNorm() < this->balls[0].getR2())
			{
			
				this->balls[0].hit(-this->shotVec*4, this->ballHit);
				this->shooting = WAITING;
				this->cue->setPosition(Eigen::Vector3f(-10,-10,0));
			}
		}
		angle = atan2(this->drawBackDir[1], this->drawBackDir[0])*(180 / 3.14159265359) - 90;
		this->cue->setPosition(this->balls[0].getPosition()+this->drawBack);
	}
	else if(this->shooting == WAITING)
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

}

void Pool::collisionTest(float dt)
{
	
	for (int i = 0; i < 7; i++)
	{
		// balls
		for (int u = 1; u < 15; u++)
		{
			if(i!=u)
				this->collision(i, u, dt);
		}
		// table

	}
	
	// table
	for (int u = 0; u < 15; u++){	
		//this->collision(this->balls[u], *this->table);	
		this->collision(u);
	}


}
bool Pool::collision(int ballId)
{
	Eigen::Vector3f v = this->balls[ballId].getVelocity();
	Eigen::Vector3f table_pos = this->table->getPosition();
	Eigen::Vector3f table_size = this->table->getSize();

	int collision = 0;
	int k = 0; //to flip ep and en
	if (this->balls[ballId].getPosition()[1] - radius_BALL <= table_pos[1] - table_size[1]) {
		collision = 1; //top
		this->balls[ballId].setPosition(Eigen::Vector3f(this->balls[ballId].getPosition()[0], table_pos[1] - table_size[1] + radius_BALL, 0));
		k = 1;
	}
	else if (this->balls[ballId].getPosition()[1] + radius_BALL >= table_pos[1] + table_size[1]) {
		collision = 2; //bot
		this->balls[ballId].setPosition(Eigen::Vector3f(this->balls[ballId].getPosition()[0], table_pos[1] + table_size[1] - radius_BALL, 0));
		k = 1;
	}
	else if (this->balls[ballId].getPosition()[0] - radius_BALL <= table_pos[0] - table_size[0]) {
		collision = 3; //left
		this->balls[ballId].setPosition(Eigen::Vector3f(table_pos[0] - table_size[0] + radius_BALL, this->balls[ballId].getPosition()[1], 0));
	}
	else if (this->balls[ballId].getPosition()[0] + radius_BALL >= table_pos[0] + table_size[0]) {
		collision = 4; //right
		this->balls[ballId].setPosition(Eigen::Vector3f(table_pos[0] + table_size[0] - radius_BALL, this->balls[ballId].getPosition()[1], 0));
	}

	if (collision > 0) {
		Eigen::Vector3f u(0, 0, 0);
		u[k] = v[k] * e_BALL_WALL * -1;
		float dvy = u[1] - this->balls[ballId].getVelocity()[1];
		u[1-k] = v[1-k] * 5 / 7;
		this->balls[ballId].setVelocity(u);
		this->balls[ballId].setAcceleration(u.normalized() * u_BALL_CLOTH_ROLL * _g * -1);
	}
	
	return true;


}

bool Pool::collision(unsigned int id1, unsigned int id2, float delta)
{
	if (((this->balls[id1].getPosition() - this->balls[id2].getPosition()).norm()) <= 2 * radius_BALL) 
	{
		
		this->balls[id1].changePosition(-this->balls[id1].getVelocity()*delta);
		this->balls[id2].changePosition(-this->balls[id2].getVelocity()*delta);

		Eigen::Vector2f ep = (this->balls[id1].getPosition() - this->balls[id2].getPosition()).head<2>().normalized();
		Eigen::Vector2f en(-ep[1], ep[0]);

		float v1p = this->balls[id1].getVelocity().head<2>().dot(ep), v2p = this->balls[id2].getVelocity().head<2>().dot(ep);
		float u1p = 0.5 * (1 - e_BALL_BALL) * v1p - 0.5 * (1 + e_BALL_BALL) * v2p,
			u2p = 0.5 * (1 + e_BALL_BALL) * v1p - 0.5 * (1 - e_BALL_BALL) * v2p;

		Eigen::Vector2f u1 = this->balls[id1].getVelocity().head<2>() + (u1p - v1p)*(ep + u_BALL_BALL*en);
		Eigen::Vector2f u2 = this->balls[id2].getVelocity().head<2>() + (u2p - v2p)*(ep + u_BALL_BALL*en);

		this->balls[id1].setVelocity(Eigen::Vector3f(u1[0], u1[1], 0));
		this->balls[id2].setVelocity(Eigen::Vector3f(u2[0], u2[1], 0));
		this->balls[id1].setAcceleration(this->balls[id1].getVelocity().normalized()* u_BALL_CLOTH_ROLL * _g * -1);
		this->balls[id2].setAcceleration(this->balls[id2].getVelocity().normalized()* u_BALL_CLOTH_ROLL * _g * -1);

		//spin
		Eigen::Vector3f w1_dir = Eigen::Vector3f(u1[0], u1[1], 0).cross(Eigen::Vector3f(0, 0, 1)).normalized();
		Eigen::Vector3f w2_dir = Eigen::Vector3f(u2[0], u2[1], 0).cross(Eigen::Vector3f(0, 0, 1)).normalized();
		
		Eigen::Vector2f w1xy = Eigen::Vector2f(w1_dir[0], w1_dir[1]) * u_BALL_CLOTH_SLIDE * _g * -1;
		Eigen::Vector2f w2xy = Eigen::Vector2f(w2_dir[0], w2_dir[1]) * u_BALL_CLOTH_SLIDE * _g * -1;

		this->balls[id1].setRotationAcceleration(Eigen::Vector3f(w1xy[0], w1xy[1], a_rota_BALL_CLOTH));
		this->balls[id2].setRotationAcceleration(Eigen::Vector3f(w2xy[0], w2xy[1], a_rota_BALL_CLOTH));

		return true;
	}
	else
		return false;

}


void Pool::holeTest(int ballId)
{
	Eigen::Vector3f pos;
	float hole_r = 0.05;
	
	Eigen::Vector3f h[6];

	h[0] = Eigen::Vector3f(0.1, 0.1, 0);
	h[1] = Eigen::Vector3f(1.3, 0.07, 0);
	h[2] = Eigen::Vector3f(2.5, 0.1, 0);
	h[3] = Eigen::Vector3f(0.1, 1.2, 0);
	h[4] = Eigen::Vector3f(1.3, 1.23, 0);
	h[5] = Eigen::Vector3f(2.5, 1.2, 0);

	
	pos = this->balls[ballId].getPosition();

	for (int i = 0; i < 6; i++) {
		if ((pos - h[i]).norm() < hole_r) {
			this->balls[ballId].setPosition(Eigen::Vector3f(-10, -10, 0));
			this->balls[ballId].setVelocity(Eigen::Vector3f(0, 0, 0));
			this->balls[ballId].setAcceleration(Eigen::Vector3f(0, 0, 0));
			this->balls[ballId].setRotationAcceleration(Eigen::Vector3f(0, 0, 0));
			this->balls[ballId].setRotationVelocity(Eigen::Vector3f(0, 0, 0));
			this->balls[ballId].setRotation(Eigen::Vector3f(0, 0, 0));
			if (ballId == 0)
			{
				this->shooting = HOLDING;
			}
		}
	}
	
}


