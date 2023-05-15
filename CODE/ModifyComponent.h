/*

The modify component is used to change the existing entity into a different type
this is used by almost every entity in the game

 a key gameplay element is that a type of entity (which kills the player)
 slowly takes over the level, this is done by changing the entity type (world type) of the existing entities
 the existing entities are changed to a destroyed type

*/

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
	int currentEdge = 29;
	int currentDestroyed = 30;

	double frameTime;
	double currentTime = 0.0;
	int runTime = 10;

public:
	// constructor - sets the row number of the entity
	ModifyComponent(int r)
	{
		rowNumber = r;
	}

	// initialise the components required variables
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

	// changes world type of the entity to destroyed
	// if the row number is equal to the current destroyed
	void update() override
	{
		if (worldType == Point)
		{
			worldType = entity->getWorldType();
		}
		if (worldType != Destroyed)
		{
			frameTime = entity->getGameTime();
			if (currentTime >= runTime)
			{
				currentTime = 0.0;
				currentDestroyed--;
				currentEdge--;


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

	// sets the entity world type to destroyedEdge
	void toDestroyedEdge();

	// sets the entity world type to destroyed
	void toDestroyed();

	// sets the entity world type to DestroyedEdge from point
	void pointDestroyedEdge();

};