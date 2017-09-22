#pragma once
#ifndef AppWindow_H
#define AppWindow_H
#include "Struct.h"
#include "Settings.h"



class AppWindow
{
public:
	AppWindow();
	AppWindow(Settings settings);
	~AppWindow();

	void setWindowPosition(vec pos);
	void setWindowSize(vec size);
	void setState(int state);
	void setName(LPCTSTR name);

	bool createClass(HINSTANCE hInstance, WNDPROC wndProc);
	bool createWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow, Settings* settings);
	bool updateWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow, Settings* settings);

private:
	struct appWindowMetrics
	{
		vec pos;
		vec size;
		int state;
		LPCTSTR name;
	};
	appWindowMetrics appWindow;
};

#endif