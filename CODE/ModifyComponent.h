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

	bool running = false;
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
	}

	void update() override
	{
		if (worldType != Destroyed)
		{
			if (running == true)
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

	void toDestroyedEdge()
	{
		entity->setWorldType(DestroyedEdge);
		Vector2D position = pTC->getPosition();
		pIC->setImage("destroyedEdge");
		pCC->setActive(true);
	}

	void toDestroyed()
	{
		entity->setWorldType(Destroyed);
		Vector2D position = pTC->getPosition();
		pIC->setImage("destroyed");
		pCC->setActive(false);
	}

	void pointDestroyedEdge()
	{
		entity->setWorldType(DestroyedEdge);
		pTC->addPosition(Vector2D(0, 16));
		pIC->setImage("destroyedEdge");
		pCC->setActive(true);
	}

	void setRunning(bool r)
	{
		running = r;
	}

};