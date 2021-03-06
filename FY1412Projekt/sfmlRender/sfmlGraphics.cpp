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
	this->windowSpec.resolution = settings->getResolution();
	this->windowSpec.fullScreen = settings->getFullScreen();
	this->windowSpec.vSync = settings->getVsync();
	this->pixelSize = 1/(2.6 / (1920-100));
	

	if (!font1.loadFromFile("BebasNeue.otf"))
	{
		return false;
	}


	this->poolTable.setFillColor(sf::Color::White);
	this->poolTable.setPosition(0,0);
	this->poolTable.setSize(sf::Vector2f(2.6*this->pixelSize, 1.3*this->pixelSize));
	this->texs[16].loadFromFile("Pics/Table.png");
	this->poolTable.setTexture(&this->texs[16]);


	for (int i = 0; i < 15; i++)
	{
		std::string fileName = "Pics/" + to_string(i) + ".png";
		
		this->texs[i].loadFromFile(fileName);

		this->balls[i].setPosition(i * 50, i * 50);
		this->balls[i].setRadius(0.028*this->pixelSize);
		this->balls[i].setFillColor(sf::Color::White);
		this->balls[i].setTexture(&this->texs[i]);
		this->balls[i].setOrigin(sf::Vector2f(0.028*this->pixelSize, 0.028*this->pixelSize));
	}

	this->texs[15].loadFromFile("Pics/Cue.png");
	this->cue.setTexture(&this->texs[15]);
	this->cue.setSize(sf::Vector2f(0.03*this->pixelSize,1.5*this->pixelSize));
	this->cue.setFillColor(sf::Color::White);
	this->cue.setOrigin(sf::Vector2f(0.015*this->pixelSize,0));

	//
	this->balls[0].setTexture(&this->texs[11]);

	//this->dot.setFillColor(sf::Color::Red);
	//this->dot.setOrigin(5, 5);
	//this->dot.setRadius(5);


	return true;
}

void sfmlGraphics::beginRender()
{
	this->window->setActive();
	this->window->clear(Color::Black);

	this->window->draw(this->poolTable);
	this->balls[0].setPosition(2.6677*this->pixelSize, 0.0677*this->pixelSize);
	this->balls[0].setScale(2.3, 2.3);
	this->window->draw(this->balls[0]);
	this->balls[0].setScale(1, 1);
}

void sfmlGraphics::render(Actor* toRender)
{

	unsigned int idx = toRender->getID();
	Eigen::Vector3f pos = toRender->getPosition()*this->pixelSize;
	if (idx < 15)
	{
		this->balls[idx].setPosition(pos[0], pos[1]);
		this->balls[idx].setRotation(toRender->getRotation()[2] * 180 / 3.1415);
		this->window->draw(this->balls[idx]);

		//if (idx == 0) {
		//	Eigen::Vector3f r = toRender->getRotation().normalized();
		//	this->dot.setPosition(pos[0] + r[0] * this->pixelSize, pos[1]);
		//	//if (toRender->getRotation()[2] > 0)
		//		this->window->draw(this->dot);
		//}
	}
	if (idx == 15)
	{
		this->cue.setPosition(pos[0], pos[1]);
		this->cue.setRotation(toRender->getRotation()[2]);
		this->window->draw(this->cue);
		this->renderText(to_string(toRender->getRotation()[2]),200,200);
	}


}

void sfmlGraphics::renderText(std::string txt, int x, int y)
{
	sf::Text toRender;
	toRender.setCharacterSize(20);
	toRender.setFont(this->font1);
	toRender.setPosition(x, y);
	toRender.setString(txt);
	this->window->draw(toRender);
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










//Text text;
//text.setFont(font1);
//text.setString("watafaq");
//text.setCharacterSize(50);
//text.setFillColor(Color::Black);
//
//
//text.setOutlineColor(Color::Black);

//this->window->draw(text);
