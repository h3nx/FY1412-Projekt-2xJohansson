#pragma once
#include <vector>

#include <string>

class KeyBinds
{
public:
	KeyBinds();
	~KeyBinds();
	struct Key
	{
		bool active = false;
		bool locked = false;
		bool toggled = false;
	};
	struct Bind
	{
		unsigned int bind;
		std::string name;
	};
	Key getKey(unsigned int key);
	
	void addBind(unsigned int key, std::string name);
	void addBind(Bind bind);
	int changeBind(unsigned int index, unsigned int key);
	Bind getKeyBind(unsigned int index);
	
	void down(unsigned int key);
	void up(unsigned int key);
	void lock(unsigned int key);
	void toggle(unsigned int key, bool value);

	bool isBindDown(unsigned int key);
	bool isLocked(unsigned int key);
	bool toggled(unsigned int key);

private:
	
	
	Key *keys;
	std::vector<Bind> keybinds;
	
};

