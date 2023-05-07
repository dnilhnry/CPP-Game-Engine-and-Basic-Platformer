/*

The AnimationComponent is responsible for modifying an entities image or orientation

*/

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

	// The init method is used to setup the component
	// It initializes all of the required variables
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

	// The update method is used to update the component
	// If the component is active, it will update the entities animation
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
	// the players physics determines the animation
	void playerAnimation();

	// If the player wins the game
	// the player will be animated to celebrate
	void playerWin();

	// If the player loses the game
	// the player will be animated to die
	void playerLose();


	// platform animations
	// if the platform is a trapped platform with an animation component
	// the platform will be rotated 180degrees every 5 seconds
	void platformAnimation();

};