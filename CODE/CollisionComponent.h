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
	Rectangle2D collisionBox;
	Circle2D collisionCircle;
	bool collisionActive;

public:
	void init() override
	{
		entityType = entity->getEntityType();
		worldType = entity->getWorldType();
		pTC = &entity->getComponent<TransformComponent>();
		collisionActive = true;

		if (entityType == Character)
		{
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
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
			}
			if (worldType == Platform)
			{
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 8), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 8));
			}
			if (worldType == TrappedPlatform)
			{
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 8), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 8));
			}
			if (worldType == Trap)
			{
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
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
			}
			if (worldType == Destroyed)
			{
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
			}
			if (worldType == Exit)
			{
				collisionBox = Rectangle2D();
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
			}
			if (worldType == Point)
			{
				collisionCircle = Circle2D(Vector2D(pTC->getPosition().XValue, pTC->getPosition().YValue), 8);
			}
		}
	}

	void update() override
	{
		if (entityType == Character)
		{
			collisionCircle = Circle2D(Vector2D(pTC->getPosition().XValue, pTC->getPosition().YValue), 32);
		}
	}

	void checkCollision(std::vector<Entity*>& collidersVector)
	{
		for (auto& entity : collidersVector)
		{
			bool collided = false;
			Vector2D collisionDirection = Vector2D(0, 0);
			if (entity->getComponent<CollisionComponent>().getActive() == true)
			{
				/*if (check for collisions with player)
				{
					collisionDirection = something;
					collided = true;
				}*/

				if (collided == true)
				{
					WorldType colliderType = entity->getWorldType();
					if (colliderType == Platform)
					{
						// if collided with top
						pPC->stableGround();
						// else if collided with bottom
						pGC->setLose(false);
					}
					if (colliderType == TrappedPlatform)
					{
						// if collided with platform
						pPC->stableGround();
						// else if collided with trap
						pGC->setLose(false);
					}
					if (colliderType == Trap)
					{
						pGC->setLose(false);
					}
					if (colliderType == DestroyedEdge)
					{
						pGC->setLose(false);
					}
					if (colliderType == Exit)
					{
						pGC->setWin(true);
					}
					if (colliderType == Point)
					{
						entity->getComponent<CollisionComponent>().setActive(false);
						entity->setWorldType(Empty);
						entity->getComponent<TransformComponent>().addPosition(Vector2D(0, 16));
						entity->getComponent<ImageComponent>().setImage("empty");
						// pGC->increasePoints();
					}
				}
			}
		}
	}

	void setActive(bool condition)
	{
		collisionActive = condition;
	}

	bool getActive()
	{
		return collisionActive;
	}

};