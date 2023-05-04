#pragma once

#include "Components.h"

class AnimationComponent : public Component
{
private:
	ImageComponent* pIC;

	TransformComponent* pTC;
	PhysicsComponent* pPC;

	// frame variables to control animation


public:
	AnimationComponent()
	{

	}

	void init() override
	{

	}

	void update() override
	{

	}

	// player animations

};