#include <Windows.h>
#include "FrameWork\Application.h"
#include "Eigen\Geometry"
using namespace Eigen;

Application app;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define PI 3.14159265
#define rad PI/180
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	MSG msg = { 0 };
	
	

	Eigen::Vector3f x(1, 0, 0);
	Eigen::Vector3f y(0, 1, 0);

	Eigen::Vector3f z = x.cross(y);



	if (app.init(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WndProc))
	{
		app.run();

	}
	else
		return 100;

	while (app.processMessage(msg))
		app.update();

	return app.getExitValue();
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	app.input(&message, &wParam, &lParam);
	return DefWindowProc(hWnd, message, wParam, lParam);
}