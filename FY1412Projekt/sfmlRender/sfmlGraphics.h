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
	void beginRender() ;
	void render();
	void endRender();

	void drawThis(sf::CircleShape *shapes);

private:
	
	WindowHandle sfmlhandle;
	RenderWindow* window;
	Font font1;
	
	
};

