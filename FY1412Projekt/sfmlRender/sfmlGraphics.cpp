#include "sfmlGraphics.h"



sfmlGraphics::sfmlGraphics()
{
}


sfmlGraphics::~sfmlGraphics()
{
	delete this->something;
}

bool sfmlGraphics::init(HWND handle, Settings * settings)
{
	this->sfmlhandle = handle;
	this->something = new Window(handle);




	return false;
}

void sfmlGraphics::beginRender()
{



}

void sfmlGraphics::render()
{



}

void sfmlGraphics::endRender()
{




}

