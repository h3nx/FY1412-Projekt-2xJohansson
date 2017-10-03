#include "KeyBinds.h"



KeyBinds::KeyBinds()
{
	this->keys = new Key[256];
}


KeyBinds::~KeyBinds()
{
	delete keys;
}

KeyBinds::Key KeyBinds::getKey(unsigned int key)
{
	return this->keys[key];
}

void KeyBinds::addBind(unsigned int key, std::string name)
{
	this->keybinds.push_back({ key,name });
}
void KeyBinds::addBind(Bind bind)
{
	this->keybinds.push_back(bind);
}
int KeyBinds::changeBind(unsigned int index, unsigned int key)
{
	int size = this->keybinds.size();
	int ret = -1;
	for (int i = 0; i < size; i++)
		if (this->keybinds[i].bind == key)
		{
			ret = i;
			this->keybinds[i].bind = 0;
		}

	this->keybinds[index].bind = key;


	return ret;
}

bool KeyBinds::isBindDown(unsigned int bind)
{
	return this->keys[this->keybinds[bind].bind].active;
}

bool KeyBinds::toggled(unsigned int key)
{
	return this->keys[key].toggled;
}

KeyBinds::Bind KeyBinds::getKeyBind(unsigned int index)
{
	return this->keybinds[index];
}

void KeyBinds::down(unsigned int key)
{
	this->keys[key].active = true;
}

void KeyBinds::up(unsigned int key)
{
	this->keys[key].active = false;
	this->keys[key].locked = false;
}

void KeyBinds::lock(unsigned int key)
{
	if (this->keys[key].active)
		this->keys[key].locked = true;
}

void KeyBinds::toggle(unsigned int key, bool value)
{
}
