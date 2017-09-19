#pragma once
#ifndef Window_H
#define Window_H
#include "Struct.h"
#include "Settings.h"



class Window
{
public:
	Window();
	Window(Settings settings);
	~Window();

	void setWindowPosition(vec pos);
	void setWindowSize(vec size);
	void setState(int state);
	void setName(LPCTSTR name);

	bool createClass(HINSTANCE hInstance, WNDPROC wndProc);
	bool createWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow, Settings* settings);
	bool updateWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow, Settings* settings);

private:
	struct AppWindow
	{
		vec pos;
		vec size;
		int state;
		LPCTSTR name;
	};
	AppWindow appWindow;
};

#endif