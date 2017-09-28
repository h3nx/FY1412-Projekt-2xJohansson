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
	if (window)
		float asd;
	this->beginRender();
	this->endRender();

	if (!font1.loadFromFile("BebasNeue.otf"))
	{
		return false;
	}


	return true;
}

void sfmlGraphics::beginRender()
{
	this->window->setActive();
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

	CircleShape asd;
	
}

void sfmlGraphics::endRender()
{
	this->window->display();
	this->window->setActive(false);



}

void sfmlGraphics::drawThis(sf::CircleShape *shapes)
{
	this->window->draw(*shapes);
}

