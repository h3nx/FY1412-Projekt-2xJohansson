#include "Window.h"



Window::Window()
{

	this->appWindow.name = L"Node";
	this->appWindow.pos = { 0,0 };
	this->appWindow.size = { 640,480 };
	this->appWindow.state = 0;
}

Window::Window(Settings settings)
{




}


Window::~Window()
{
}

void Window::setWindowPosition(vec pos)
{
	this->appWindow.pos = pos;
}
void Window::setWindowSize(vec size)
{
	this->appWindow.size = size;
}
void Window::setState(int state)
{
	this->appWindow.state = state;
}

void Window::setName(LPCTSTR name)
{
	this->appWindow.name = name;
}


bool Window::createClass(HINSTANCE hInstance, WNDPROC wndProc)
{



	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = L"ApplicationXYZ";
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	//wcex.hIcon = LoadIcon(*this->hInstanceP, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(2);
	wcex.lpszMenuName = NULL;
	//wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
		return false;
	return true;
}

bool Window::createWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow, Settings* settings)
{
	DWORD style;
	vec pos = { 0,0 };
	vec addSize = { 0,0 };
	if (settings->getFullScreen() == 0)
	{
		style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
		pos = { 0-SM_CXBORDER-1,0 };
		addSize = { SM_CXBORDER * 2,SM_CXBORDER * 2 };
	}
	if (settings->getFullScreen() >= 1)
		style = WS_EX_TOPMOST | WS_POPUP;


	hwnd = CreateWindowEx(
		NULL,
		L"ApplicationXYZ",
		this->appWindow.name,
		style,
		pos.x,
		pos.y,
		settings->getResolution().x+addSize.x,
		settings->getResolution().y+addSize.y,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);





	if (hwnd == NULL)
		return false;
	ShowWindow(hwnd,nCmdShow);
	return true;
}

bool Window::updateWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow, Settings* settings)
{
	DestroyWindow(hwnd);
	hwnd = NULL;
	return this->createWindow(hwnd, hInstance, nCmdShow, settings);
}
