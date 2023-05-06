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
	
	bool collisionActive;
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
		collisionActive = true;

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
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
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
				collisionBox.PlaceAt(Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32), Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 32));
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

	void checkCollision(std::vector<Entity*>& collidersVector)
	{
		for (auto& otherEntity : collidersVector)
		{
			CollisionComponent* pOtherCC = &otherEntity->getComponent<CollisionComponent>();
			Rectangle2D otherCollisionBox;
			Circle2D otherCollisionCircle;
			bool collided = false;
			Vector2D collisionDirection = Vector2D(0, 0);
			if (pOtherCC->getActive() == true)
			{				
				if (pOtherCC->getCollisionShape() == "box")
				{
					otherCollisionBox = pOtherCC->getCollisionBox();
					if (collisionCircle.Intersects(otherCollisionBox) == true)
					{
						collisionDirection = collisionCircle.CollisionNormal(otherCollisionBox);
						collided = true;
					}
				}
				if (pOtherCC->getCollisionShape() == "circle")
				{
					otherCollisionCircle = pOtherCC->getCollisionCircle();
					if (collisionCircle.Intersects(otherCollisionCircle) == true)
					{
						collisionDirection = collisionCircle.CollisionNormal(otherCollisionCircle);
						collided = true;
					}
				}
				
				if (collided == true)
				{
					WorldType colliderType = otherEntity->getWorldType();
					if (colliderType == Platform)
					{
						if (collisionDirection == Vector2D(0, -1))
						{
							pPC->stableGround();
						}
					}
					if (colliderType == TrappedPlatform)
					{
						if (collisionDirection == Vector2D(0, -1))
						{
							pPC->stableGround();
						}
						if (collisionDirection == Vector2D(0, 1))
						{
							pGC->setLose(true);
							pAC->playerDead();
							pSC->setSound("playerDeath");
							pSC->play();
						}
					}
					if (colliderType == Trap)
					{
						pGC->setLose(true);
						pAC->playerDead();
						pSC->setSound("playerDeath");
						pSC->play();
					}
					if (colliderType == DestroyedEdge)
					{
						pGC->setLose(true);
						pAC->playerDead();
						pSC->setSound("playerDeath");
						pSC->play();
					}
					if (colliderType == Exit)
					{
						pGC->setWin(true);
					}
					if (colliderType == Point)
					{
						otherEntity->getComponent<CollisionComponent>().setActive(false);
						otherEntity->setWorldType(Empty);
						otherEntity->getComponent<TransformComponent>().addPosition(Vector2D(0, 16));
						otherEntity->getComponent<ImageComponent>().setImage("empty");
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

	const char* getCollisionShape()
	{
		return collisionShape;
	}

	Rectangle2D getCollisionBox()
	{
		return collisionBox;
	}

	Circle2D getCollisionCircle()
	{
		return collisionCircle;
	}

};