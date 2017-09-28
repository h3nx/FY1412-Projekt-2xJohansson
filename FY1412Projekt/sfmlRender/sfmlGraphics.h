#pragma once
#include "..\FrameWork\Graphics.h"
#include <SFML\Graphics.hpp>
using namespace sf;



class sfmlGraphics :
	public Graphics
{
public:
	sfmlGraphics();
	~sfmlGraphics();

	bool init(HWND handle, Settings* settings);
	void beginRender();
	void render(Actor* toRender);
	void endRender();

	void drawThis(sf::CircleShape *shapes);

private:

	sf::WindowHandle sfmlhandle;
	sf::RenderWindow* window;
	sf::Font font1;

	double pixelSize;
	sf::Texture texs[20];
	sf::CircleShape balls[15];
	sf::RectangleShape poolTable;



};

