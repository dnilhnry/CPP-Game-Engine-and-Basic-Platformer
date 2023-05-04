#pragma once

#include "Components.h"
#include "Vector2D.h"

class CollisionComponent : public Component
{
private:
	


	double frameTime;

public:
	CollisionComponent()
	{
		
	}

	void init() override
	{
		
	}

	void update(double ft) override
	{
		frameTime = ft;
	}

};