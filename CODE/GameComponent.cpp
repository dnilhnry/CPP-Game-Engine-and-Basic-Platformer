#include "Components.h"

void GameComponent::setWin(bool w)
{
	win = w;
}

bool GameComponent::getWin()
{
	return win;
}

void GameComponent::setLose(bool l)
{
	lose = l;
}

bool GameComponent::getLose()
{
	return lose;
}

void GameComponent::increaseScore()
{
	score++;
}

int GameComponent::getScore()
{
	return score;
}