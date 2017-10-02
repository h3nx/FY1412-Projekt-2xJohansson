#pragma once
#include "../FrameWork/Struct.h"
#include "../FrameWork/Settings.h"
#include "../FrameWork/Actor.h"
class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	virtual bool init(HWND handle, Settings* settings) = 0;

	virtual void beginRender() = 0;
	virtual void render(Actor* toRender) = 0;
	virtual void renderText(std::string txt, int x, int y) = 0;
	virtual void endRender() = 0;

protected:
	HWND handle;
	struct windowSpecs
	{
		vec size;
		vec resolution;
		bool vSync = 0;
		int fullScreen = 0;

	};
	windowSpecs windowSpec;
};

