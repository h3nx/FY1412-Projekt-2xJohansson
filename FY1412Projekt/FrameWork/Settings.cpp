#include "Settings.h"



Settings::Settings()
{
	this->windowPos = { 0,0 };
	this->resolution = { 640,560 };
	this->fullScreen = 0;
	this->renderEngine = 1;
	this->vSync = 0;
	this->FoV = 90;
	this->shadows = 4;





}

Settings::Settings(string fileName):Settings()
{
	this->Load(fileName);
}


Settings::~Settings()
{


}

void Settings::Load(string fileName)
{
	std::fstream fileIn(fileName.c_str());
	if(fileIn)
	while (fileIn)
	{
		std::string in;
		fileIn >> in;

		if (in == "resolution:")
		{
			fileIn >> this->resolution.x >> this->resolution.y;
			continue;
		}
		if (in == "position:")
		{
			fileIn >> this->windowPos.x >> this->windowPos.y;
			continue;
		}
		if (in == "fullscreen:")
		{
			fileIn >> this->fullScreen;
			continue;
		}
		if (in == "renderengine:")
		{
			fileIn >> this->renderEngine;
			continue;
		}
		if (in == "vsync:")
		{
			fileIn >> this->vSync;
			continue;
		}
		if (in == "fov:")
		{
			fileIn >> this->FoV;
			continue;
		}
		if (in == "shadows:")
		{
			fileIn >> this->shadows;
			continue;
		}
		



		fileIn.close();
	}
	else
		this->save();
}

void Settings::save()
{
	std::ofstream fileOut("Settings.txt");


	if(fileOut)
	{
		
		fileOut << "position: " << this->windowPos.x << " " << this->windowPos.y << endl;
		fileOut << "resolution: " << this->resolution.x << " " << this->resolution.y << endl;
		fileOut << "fullscreen: " << this->fullScreen << endl;
		fileOut << "renderengine: " << this->renderEngine << endl;
		fileOut << "vsync: " << this->vSync << endl;
		fileOut << "fov: " << this->FoV << endl;
		fileOut << "shadows: " << this->shadows << endl;
	}
}

vec Settings::getWindowPos()
{
	return this->windowPos;
}

vec Settings::getResolution()
{
	return this->resolution;
}

int Settings::getFullScreen()
{
	return this->fullScreen;
}

int Settings::getRenderEngine()
{
	return this->renderEngine;
}

bool Settings::getVsync()
{
	return this->vSync;
}

int Settings::getFoV()
{
	return this->FoV;
}

int Settings::getShadows()
{
	return this->shadows;
}

void Settings::setWindowPos(vec pos)
{
	this->windowPos = windowPos;
}

void Settings::setResolution(vec res)
{
	this->resolution = res;
}

void Settings::setWindowSize(vec size)
{
	this->windowSize = size;
}

void Settings::setFullScreen(int fullScreen)
{
	this->fullScreen = fullScreen;
}

void Settings::setRenderEngine(int engine)
{
	this->renderEngine = engine;
}

void Settings::setVsync(bool vSync)
{
	this->vSync = vSync;
}

void Settings::setFoV(int FoV)
{
	this->FoV = FoV;
}

void Settings::setShadows(int shadows)
{
	this->shadows = shadows;
}


