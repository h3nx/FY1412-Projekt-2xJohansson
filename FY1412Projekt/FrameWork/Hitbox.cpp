#include "Hitbox.h"



Hitbox::Hitbox()
{
	this->root = new HitNode(Vector4f(0, 0, 0, 0), 0);
}
Hitbox::Hitbox(float radius):Hitbox()
{
	this->root = new HitNode(Vector4f(0, 0, 0, 0), radius);
}

Hitbox::~Hitbox()
{
	delete this->root;
}



int Hitbox::collision(HitNode & something)
{
	


	return 0;
}





Hitbox::HitNode::HitNode(Vector4f position, float radius)
{
	this->position = position;
	this->radius2 = radius*radius;
	for (int i = 0; i < 4; i++)
		this->children[i] = nullptr;
}

Hitbox::HitNode::~HitNode()
{

}

void Hitbox::HitNode::addNode(Vector4f position, float radius)
{


}

int Hitbox::HitNode::collision(Vector4f position, float radius2)
{
	float lengthSq = (this->position - position).squaredNorm();
	if (lengthSq > this->radius2+radius2)
		return 0;
	else if (this->radius2 > lengthSq + radius2)
		return -1;
	return 1;
}

