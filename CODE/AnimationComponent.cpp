#include "Components.h"

// player animations
void AnimationComponent::playerAnimation()
{
	float playerYVelocity = pPC->getVelocity().YValue;
	if (playerYVelocity < 1 && playerYVelocity > -1)
	{
		pIC->setImage("playerConfused");
	}
	else if (playerYVelocity <= -1)
	{
		pIC->setImage("playerScared");
	}
	else if (playerYVelocity >= 1)
	{
		pIC->setImage("playerSmiley");
	}
}

void AnimationComponent::playerWin()
{
	pIC->setImage("playerSmiley");
	setActive(false);
}

void AnimationComponent::playerLose()
{
	pIC->setImage("playerDead");
	setActive(false);
}

// platform animations
void AnimationComponent::platformAnimation()
{
	pTC->addRotation(3.142f);
}