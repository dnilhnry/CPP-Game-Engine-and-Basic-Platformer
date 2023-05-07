/*

this component is used to check if the game is won or lost
it should be added to the player entity

*/

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

	// sets bool win to given input
	void setWin(bool w);

	// gets bool win
	bool getWin();

	// sets bool lose to given input
	void setLose(bool l);

	// gets bool lose
	bool getLose();

};