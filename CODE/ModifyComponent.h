#pragma once

#include "Components.h"

class ModifyComponent : public Component
{
private:
	TransformComponent* pTC;
	ImageComponent* pIC;
	CollisionComponent* pCC;

	EntityType entityType;
	WorldType worldType;

	int rowNumber;
	int currentEdge = 1;
	int currentDestroyed = 0;

	double frameTime;
	double currentTime = 0.0;
	int runTime = 10;

public:
	ModifyComponent(int r)
	{
		rowNumber = r;
	}

	void init() override
	{
		entityType = entity->getEntityType();
		worldType = entity->getWorldType();
		pTC = &entity->getComponent<TransformComponent>();
		pIC = &entity->getComponent<ImageComponent>();
		pCC = &entity->getComponent<CollisionComponent>();
		frameTime = 0;
		setActive(false);
	}

	void update() override
	{
		if (worldType == Point)
		{
			worldType = entity->getWorldType();
		}
		if (worldType != Destroyed)
		{
			if (isActive() == true)
			{
				frameTime = entity->getGameTime();
				if (currentTime >= runTime)
				{
					currentTime = 0.0;
					currentDestroyed++;
					currentEdge++;


					if (rowNumber == currentEdge)
					{
						if (worldType != Point)
						{
							toDestroyedEdge();
						}
						else if (worldType == Point)
						{
							pointDestroyedEdge();
						}

					}
					else if (rowNumber == currentDestroyed)
					{
						toDestroyed();
					}

				}
				else
				{
					currentTime = currentTime + frameTime;
				}
			}
		}
	}

	void toDestroyedEdge();

	void toDestroyed();

	void pointDestroyedEdge();

};