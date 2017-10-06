#pragma once
#ifndef Application_H
#define Application_H
#include "Struct.h"
#include "AppWindow.h"
#include "KeyBinds.h"
#include "Settings.h"
#include "timer.h"
#include "../Game/Pool.h"
#include "MouseController.h"
#include <iomanip>
#include "../sfmlRender/sfmlGraphics.h"

using namespace std;
class Application
{
public:
	Application();
	~Application();

	bool init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC wndProc);
	void run();
	bool processMessage(MSG msg);
	void input(UINT* message, WPARAM* wParam, LPARAM* lParam);
	void update();

	
	int getExitValue();


private:

	void quit();

private:
	
	HWND handle;	
	HINSTANCE* hInstanceP;
	WNDPROC* WndProcP;	
	int* cmdShow;

	Settings* settings;
	AppWindow* window;
	KeyBinds* keyBinds;
	Timer* time;
	MouseController* mControl;
	Graphics* renderEngine;
	Pool* table;
	int exitValue;

	bool inv = true;
	float acc;

private:

	void render();
	void keyDown(unsigned int key);
	void keyUp(unsigned int key);
	void step(const float delta);


};

#endif