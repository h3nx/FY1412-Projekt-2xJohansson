#include "Application.h"



Application::Application()
{
	this->handle = NULL;
	this->settings = new Settings("Settings.txt");
	this->window = new AppWindow();
	this->keyBinds = new KeyBinds();
	this->time = new Timer(0.99);
	
	this->mControl = new MouseController(Eigen::Vector2f(this->settings->getResolution().x,this->settings->getResolution().y));
	this->renderEngine = nullptr;
}


Application::~Application()
{
	delete this->settings;
	delete this->window;
	delete this->keyBinds;
	delete this->mControl;
	delete this->time;
	delete this->renderEngine;
}


enum binds { FORWARD, BACK, RIGHT, LEFT, JUMP, CROUCH, SPRINT,INVENTORY,CHARACTER,MENU };
bool Application::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, WNDPROC WndProc)
{
	this->hInstanceP = &hInstance;
	this->WndProcP = &WndProc;
	this->cmdShow = &nCmdShow;


	this->window->setName(L"Node");

	if (!this->window->createClass(hInstance, WndProc))
		return false;
	if (!this->window->createWindow(this->handle, hInstance, nCmdShow, this->settings))
		return false;
	


	
	char toAdd[] = { 'W','S','D','A',VK_SPACE,VK_CONTROL,VK_SHIFT,'B','C',VK_ESCAPE};
	string nameToAdd[] = { "Forward", "Backward", "Right", "Left", "Jump", "Crouch", "Sprint", "Inventory", "Character", "Menu" };
	for(int i = 0;i<sizeof(toAdd)/sizeof(char);i++)
		this->keyBinds->addBind(toAdd[i], nameToAdd[i]);
	


	this->renderEngine = new sfmlGraphics();

	return true;
}

void Application::run()
{
	this->time->reset();
	//this->mControl->lock();

	
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Application::update()
{
	static float freq = 1 / 60;
	static float delta = 0;
	
	delta += this->time->deltaTime();

	int loops = 0;
	while (delta > freq && loops++ < 3)
	{
		delta -= freq;
		Vector4f move(
			this->keyBinds->isBindDown(RIGHT) - this->keyBinds->isBindDown(LEFT),
			this->keyBinds->isBindDown(BACK) - this->keyBinds->isBindDown(FORWARD),
			0,
			0
		);
		this->step();
		
	}
		this->render();
	
}

void Application::render()
{
	//Render engine here
	


	
	
}


bool Application::processMessage(MSG msg)
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (msg.message == WM_QUIT)
	{
		this->exitValue = msg.wParam;
		this->quit();
		return false;
	}
	return true;
}

void Application::input(UINT * message, WPARAM * wParam, LPARAM * lParam)
{

	if (*message == WM_QUIT)
	{

	}
	switch (*message)
	{

	case WM_CLOSE: {
		PostQuitMessage(1);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(2);
		break;
	}		
	case WM_MOUSEMOVE:
	{
		this->mControl->update(*lParam);
	}break;

	case WM_KEYDOWN:{
		this->keyDown(*wParam);	

		if (*wParam == VK_ESCAPE)
			PostQuitMessage(*wParam);
		break;
	}
	case WM_KEYUP:{
		this->keyBinds->up(*wParam);
		break;
	}

	case WM_LBUTTONDOWN:{
		this->keyDown(1);
		break;
	}
	case WM_LBUTTONUP:{
		this->keyUp(1);
		break;
	}
	case WM_RBUTTONDOWN:{
		this->keyDown(2);
		break;
	}
	case WM_RBUTTONUP:{
		this->keyUp(2);
		break;
	}
	case WM_MBUTTONDOWN:{
		this->keyDown(4);
		break;
	}
	case WM_MBUTTONUP:{
		this->keyUp(4);
		break;
	}

	case WM_XBUTTONDOWN:{
		this->keyDown(GET_XBUTTON_WPARAM(*wParam) == 2 ? VK_XBUTTON1 : VK_XBUTTON2);
		break;
	}
	case WM_XBUTTONUP:{
		this->keyUp(GET_XBUTTON_WPARAM(*wParam) == 2 ? VK_XBUTTON1 : VK_XBUTTON2);
		break;
	}

	case WM_MOUSELEAVE:{
		//	game->outOfFocus(false);
		//	focus = 0;
		break;
	}


	case WM_ACTIVATE:{
		if (*wParam == WA_INACTIVE)
		{
			//	game->outOfFocus(false);
			//	focus = 0;
		}
		//else if (!focus)
		//{
		//	focus = 1;
		//}
		break;
	}
	
	case WM_SIZE: {

		/*	RECT client;
			GetClientRect(handle, &client);
			RECT window;
			GetWindowRect(handle, &window);
			this->settings->setResolution(vec(client.right, client.bottom));
			this->mControl->setResolution(Vector2f(client.right, client.bottom));
			this->settings->setWindowSize(vec(window.right, window.bottom));
			*/
		break;
	}
	case WM_PAINT: {
	//	this->render();

		break;
	}


	};
}

void Application::quit()
{

	this->settings->save();

}
void Application::keyDown(unsigned int key)
{
	this->keyBinds->down(key);

	if (this->keyBinds->getKeyBind(FORWARD).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(BACK).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(RIGHT).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(LEFT).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(JUMP).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(SPRINT).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(CROUCH).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(INVENTORY).bind == key)
	{
		if (inv)
		{
			this->mControl->lock();
			this->mControl->hide();
			this->inv = false;
		}
		else if (!inv)
		{
			this->mControl->reveal();
			this->mControl->unLock();
			this->inv = true;
		}
	}
	if (this->keyBinds->getKeyBind(CHARACTER).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(MENU).bind == key)
	{


	}








}
void Application::keyUp(unsigned int key)
{
	this->keyBinds->up(key);

	if (this->keyBinds->getKeyBind(FORWARD).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(BACK).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(RIGHT).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(LEFT).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(JUMP).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(SPRINT).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(CROUCH).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(INVENTORY).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(CHARACTER).bind == key)
	{


	}
	if (this->keyBinds->getKeyBind(MENU).bind == key)
	{


	}




}
int Application::getExitValue()
{
	return this->exitValue;
}
void Application::step()
{






}


