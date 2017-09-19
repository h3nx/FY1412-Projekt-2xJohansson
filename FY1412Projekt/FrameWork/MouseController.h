#pragma once
#include "../Eigen/Core"
#include <windows.h>
#include <windowsx.h>
using namespace Eigen;
class MouseController
{
public:
	MouseController();
	MouseController(Vector2f res);
	~MouseController();

	void update(LPARAM lParam);
	bool hasMoved();


	void lock();
	void unLock();

	void hide();
	void reveal();

	void contain();
	void release();

	Vector2f getMousePos();
	Vector2f getMouseDelta();


	void setResolution(Vector2f res);


private:
	
	Vector2f resolution;
	Vector2f resolutionCentre;
	bool locked;
	bool hidden;
	bool contained;
	bool moved;

	
	Vector2f position;
	Vector2f lockedPosition;
	Vector2f delta;


private:
	Vector2f getPos(LPARAM lParam);
	void setPosition(Vector2f pos);
};

