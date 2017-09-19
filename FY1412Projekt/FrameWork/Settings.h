#pragma once
#ifndef Settings_h
#define Settings_h
#include "Struct.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>




using namespace std;
class Settings
{
public:
	Settings();
	Settings(string fileName);
	~Settings();

	void Load(string fileName);
	void save();

	vec getWindowPos();
	vec getResolution();
	int getFullScreen();
	int getRenderEngine();
	bool getVsync();
	int getFoV();
	int getShadows();

	void setWindowPos(vec pos);
	void setResolution(vec res);
	void setWindowSize(vec size);
	void setFullScreen(int fullScreen);
	void setRenderEngine(int engine);
	void setVsync(bool vSync);
	void setFoV(int FoV);
	void setShadows(int shadows);




private:

	vec windowPos;
	vec resolution;
	vec windowSize;
	int fullScreen;
	int renderEngine;
	bool vSync;
	int FoV;
	int shadows;





};

#endif