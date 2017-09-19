#include "MouseController.h"

MouseController::MouseController()
{
	this->resolution = Vector2f(0, 0);
	this->resolutionCentre = Vector2f(0, 0);
	this->locked = 0;
	this->contained = 0;

	this->position = Vector2f(0, 0);
	this->lockedPosition = Vector2f(0, 0);
	this->delta = Vector2f(0, 0);
}

MouseController::MouseController(Vector2f res):MouseController()
{
	this->setResolution(res);
}


MouseController::~MouseController()
{
}

void MouseController::update(LPARAM lParam)
{
	this->position = this->getPos(lParam);
	if (this->locked)
	{
		Vector2f newDelta = this->position - this->resolutionCentre;
		this->delta += newDelta;
		if (!(newDelta == Vector2f(0, 0)))
		{
			
			this->setPosition(this->resolutionCentre);
		}
	}
	if (this->contained)
	{
		if (this->position[0] > this->resolution[0])
			this->position[0] = this->resolution[0];
		if (this->position[0] < 0)
			this->position[0] = 0;

		this->position[1] = (this->position[1] > this->resolution[1]) ? this->resolution[1] : this->position[1];
		this->position[1] = (this->position[1] < 0) ? 0 : this->position[1];



	}




	this->moved = true;
}

bool MouseController::hasMoved()
{
	bool toRet = this->moved;
	this->moved = false;
	return toRet;
}



void MouseController::lock()
{
	this->lockedPosition = this->position;
	this->setPosition(this->resolutionCentre);
	this->position = this->resolutionCentre;
	this->locked = true;

}

void MouseController::unLock()
{
	this->setPosition(this->lockedPosition);
	this->position = this->lockedPosition;
	this->locked = false;
}

void MouseController::hide()
{
	ShowCursor(false);
}

void MouseController::reveal()
{
	ShowCursor(true);
}

void MouseController::contain()
{
	this->contained = true;
}

void MouseController::release()
{
	this->contained = false;
}

Vector2f MouseController::getMousePos()
{
	return this->position;
}

Vector2f MouseController::getMouseDelta()
{
	Vector2f toRet = this->delta;
	this->delta = Vector2f(0, 0);
	return toRet;
}

void MouseController::setResolution(Vector2f res)
{
	this->resolution = res;
	this->resolutionCentre = res*0.5;
}

Vector2f MouseController::getPos(LPARAM lParam)
{
	return Vector2f(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
}

void MouseController::setPosition(Vector2f pos)
{
	SetCursorPos(pos[0], pos[1]);
}
