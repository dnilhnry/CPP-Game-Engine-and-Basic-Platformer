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
		if (isActive() == true)
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
	}

	// player animations
	void playerAnimation();

	void playerWin();

	void playerLose();


	// platform animations
	void platformAnimation();

};