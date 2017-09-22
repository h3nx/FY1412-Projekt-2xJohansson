#include "sfmlGraphics.h"



sfmlGraphics::sfmlGraphics()
{
}


sfmlGraphics::~sfmlGraphics()
{
	delete this->window;
}

bool sfmlGraphics::init(HWND handle, Settings * settings)
{
	this->sfmlhandle = handle;
	this->window = new RenderWindow(handle);


	if (!font1.loadFromFile("BebasNeue.otf"))
	{
		return false;
	}


	return true;
}

void sfmlGraphics::beginRender()
{
	this->window->clear(Color::White);


}

void sfmlGraphics::render()
{
	Text text;
	text.setFont(font1);
	text.setString("watafaq");
	text.setCharacterSize(50);
	text.setFillColor(Color::Black);
	
	
	text.setOutlineColor(Color::Black);

	this->window->draw(text);


}

void sfmlGraphics::endRender()
{
	this->window->display();



}

