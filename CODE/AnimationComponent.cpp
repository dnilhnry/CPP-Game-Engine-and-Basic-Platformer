#include "Components.h"

// player animations
void AnimationComponent::playerAnimation()
{
	float playerYVelocity = pPC->getVelocity().YValue;
	if (playerYVelocity < 5.0f && playerYVelocity > -5.0f)
	{
		pIC->setImage("playerConfused");
	}
	else if (playerYVelocity <= -5.0f)
	{
		pIC->setImage("playerScared");
	}
	else if (playerYVelocity >= 5.0f)
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
	if (frameNumber == 0)
	{
		pTC->addPosition(Vector2D(0, 1.5f));
	}
	if (frameNumber == 1)
	{
		pTC->addPosition(Vector2D(0, -3.0f));
	}
	if (frameNumber == 2)
	{
		pTC->addPosition(Vector2D(0, 3.0f));
	}
	if (frameNumber == 3)
	{
		pTC->addPosition(Vector2D(0, -3.0f));
	}
	if (frameNumber == 4)
	{
		pTC->addPosition(Vector2D(0, 1.5f));
	}
	if (frameNumber == 5)
	{
		pTC->addRotation(3.142f);
		animationStarted = false;
	}
}