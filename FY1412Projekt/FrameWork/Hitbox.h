#pragma once
#include "../Eigen/Core"

using namespace Eigen;
class Hitbox
{
public:
	Hitbox();
	Hitbox(float radius);
	~Hitbox();

	
	class HitNode
	{
	public:
		HitNode(Vector4f position, float radius);
		~HitNode();
		
		int collision(Vector4f position, float radius);
		
	private:
		Vector4f position;
	};

	

private:
	HitNode* root;
	int collision(HitNode& something);

};

