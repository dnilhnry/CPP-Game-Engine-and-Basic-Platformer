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
	const char* collisionShape;
	Rectangle2D collisionBox;
	Circle2D collisionCircle;

public:
	void init() override
	{
		entityType = entity->getEntityType();
		worldType = entity->getWorldType();
		pTC = &entity->getComponent<TransformComponent>();

		if (entityType == Character)
		{
			collisionShape = "circle";
			collisionCircle = Circle2D(Vector2D(pTC->getPosition().XValue, pTC->getPosition().YValue), 30);
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
				collisionShape = "box";
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
			}
			if (worldType == Platform)
			{
				collisionShape = "box";
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 8), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 8));
			}
			if (worldType == TrappedPlatform)
			{
				collisionShape = "box";
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 8), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 8));
			}
			if (worldType == Trap)
			{
				collisionShape = "box";
				collisionBox = Rectangle2D();
				if (pTC->getRotation() == 0)
				{
					collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 8), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 8));
				}
				if (pTC->getRotation() == 1.571f)
				{
					collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 8, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 8, pTC->getPosition().YValue + 32));
				}
			}
			if (worldType == DestroyedEdge)
			{
				collisionShape = "box";
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 24));
			}
			if (worldType == Destroyed)
			{
				collisionShape = "box";
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
			}
			if (worldType == Exit)
			{
				collisionShape = "box";
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 24), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
			}
			if (worldType == Point)
			{
				collisionShape = "circle";
				collisionCircle = Circle2D(Vector2D(pTC->getPosition().XValue, pTC->getPosition().YValue), 8);
			}
		}
	}

	void update() override
	{
		if (entityType == Character)
		{
			position = pTC->getPosition();
			collisionCircle.PlaceAt(position, 32);
		}
	}

	void checkCollision(std::vector<Entity*>& collidersVector);

	const char* getCollisionShape();

	Rectangle2D getCollisionBox();

	Circle2D getCollisionCircle();

};