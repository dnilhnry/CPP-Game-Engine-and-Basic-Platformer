/*

The CollisionComponent class is used to check for collisions
between the player entity and all other entities that contain a CollisionComponet.
If a collision is detected, the CollisionComponent will call methods from many of the players components

*/

#pragma once

#include "Components.h"
#include "Vector2D.h"
#include "Shapes.h"

class CollisionComponent : public Component
{
private:
	EntityType entityType;
	WorldType worldType;

	GameComponent* pGC;
	TransformComponent* pTC;
	PhysicsComponent* pPC;
	ImageComponent* pIC;
	SoundComponent* pSC;
	AnimationComponent* pAC;
	
	Vector2D position;
	Vector2D lbCorner;
	Vector2D rtCorner;
	Rectangle2D collisionBox;

	double ignoreTime;
	double frameTime;

public:
	void init() override
	{
		entityType = entity->getEntityType();
		worldType = entity->getWorldType();
		pTC = &entity->getComponent<TransformComponent>();
		position = pTC->getPosition();

		collisionBox = Rectangle2D();

		if (entityType == Character)
		{
			lbCorner = Vector2D(position.XValue - 20, position.YValue - 30);
			rtCorner = Vector2D(position.XValue + 20, position.YValue + 30);
			collisionBox.PlaceAt(lbCorner, rtCorner);

			pGC = &entity->getComponent<GameComponent>();
			pPC = &entity->getComponent<PhysicsComponent>();
			pIC = &entity->getComponent<ImageComponent>();
			pSC = &entity->getComponent<SoundComponent>();
			pAC = &entity->getComponent<AnimationComponent>();
		}
		else if (entityType == World)
		{
			if (worldType == Empty)
			{
				lbCorner = Vector2D(position.XValue - 32, position.YValue - 32);
				rtCorner = Vector2D(position.XValue + 32, position.YValue + 32);
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
			if (worldType == Platform)
			{
				lbCorner = Vector2D(position.XValue - 32, position.YValue - 8);
				rtCorner = Vector2D(position.XValue + 32, position.YValue + 8);
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
			if (worldType == TrappedPlatform)
			{
				lbCorner = Vector2D(position.XValue - 32, position.YValue - 8);
				rtCorner = Vector2D(position.XValue + 32, position.YValue + 8);
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
			if (worldType == Trap)
			{
				if (pTC->getRotation() == 0)
				{
					lbCorner = Vector2D(position.XValue - 32, position.YValue - 8);
					rtCorner = Vector2D(position.XValue + 32, position.YValue + 8);
				}
				if (pTC->getRotation() == 1.571f)
				{
					lbCorner = Vector2D(position.XValue - 8, position.YValue - 32);
					rtCorner = Vector2D(position.XValue + 8, position.YValue + 32);
				}
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
			if (worldType == DestroyedEdge)
			{
				lbCorner = Vector2D(position.XValue - 32, position.YValue - 32);
				rtCorner = Vector2D(position.XValue + 32, position.YValue + 24);
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
			if (worldType == Destroyed)
			{
				lbCorner = Vector2D(position.XValue - 32, position.YValue - 32);
				rtCorner = Vector2D(position.XValue + 32, position.YValue + 32);
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
			if (worldType == Exit)
			{
				lbCorner = Vector2D(position.XValue - 32, position.YValue - 24);
				rtCorner = Vector2D(position.XValue + 32, position.YValue + 24);
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
			if (worldType == Point)
			{
				lbCorner = Vector2D(position.XValue - 8, position.YValue - 8);
				rtCorner = Vector2D(position.XValue + 8, position.YValue + 8);
				collisionBox.PlaceAt(lbCorner, rtCorner);
			}
		}
		ignoreTime = 0;
		frameTime = 0;
	}

	void update() override
	{
		frameTime = entity->getGameTime();

		if (entityType == Character)
		{
			position = pTC->getPosition();
			lbCorner = Vector2D(position.XValue - 20, position.YValue - 30);
			rtCorner = Vector2D(position.XValue + 20, position.YValue + 30);
			collisionBox.PlaceAt(lbCorner, rtCorner);
		}

		if (ignoreTime > 0)
		{
			ignoreTime = ignoreTime - frameTime;
		}
		if (ignoreTime < 0)
		{
			ignoreTime = 0;
		}
	}

	void checkCollision(std::vector<Entity*>& collidersVector);

	Rectangle2D getCollisionBox();

	void moveCollisionBox(Vector2D newLB, Vector2D newRT);

};