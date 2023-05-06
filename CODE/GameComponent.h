#pragma once

#include "Components.h"

class GameComponent : public Component
{
private:
	bool win;
	bool lose;

public:

	void init() override
	{
		win = false;
		lose = false;
	}

	void setWin(bool w)
	{
		win = w;
	}

	bool getWin()
	{
		return win;
	}

	void setLose(bool l)
	{
		lose = l;
	}

	bool getLose()
	{
		return lose;
	}

};