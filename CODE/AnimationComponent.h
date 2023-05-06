#pragma once

#include "Components.h"

class AnimationComponent : public Component
{
private:
	EntityType entityType;
	WorldType worldType;


	ImageComponent* pIC;

	TransformComponent* pTC;
	PhysicsComponent* pPC;

	double frameTime;
	double currentTime = 0.0;
	int runTime = 5;


public:
	AnimationComponent()
	{

	}

	void init() override
	{
		entityType = entity->getEntityType();
		worldType = entity->getWorldType();
		pIC = &entity->getComponent<ImageComponent>();
		pTC = &entity->getComponent<TransformComponent>();
		if (entity->hasComponent<PhysicsComponent>() == true)
		{
			pPC = &entity->getComponent<PhysicsComponent>();
		}
		else
		{
			pPC = nullptr;
		}
		frameTime = 0;
	}

	void update() override
	{
		if (entityType == Character)
		{
			playerAnimation();
		}

		if (worldType == TrappedPlatform)
		{
			frameTime = entity->getGameTime();
			if (currentTime >= runTime)
			{
				currentTime = 0.0;
				platformAnimation();
			}
			else
			{
				currentTime = currentTime + frameTime;
			}
		}
	}

	// player animations
	void playerAnimation()
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

	void playerDead()
	{
		pIC->setImage("playerDead");
	}

	// platform animations
	void platformAnimation()
	{
		pTC->addRotation(3.142f);
	}

};