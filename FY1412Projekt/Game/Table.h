#pragma once
#include "..\FrameWork\Actor.h"


class Table :
	public Actor
{
public:
	Table();
	Table(Eigen::Vector3f pos, Eigen::Vector3f size);
	~Table();
	
	void update();
	


private:





};