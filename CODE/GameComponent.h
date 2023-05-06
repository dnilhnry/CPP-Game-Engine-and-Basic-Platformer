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

	void setWin(bool w);

	bool getWin();

	void setLose(bool l);

	bool getLose();

};