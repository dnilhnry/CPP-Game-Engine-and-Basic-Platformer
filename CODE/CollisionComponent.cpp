#include "Components.h"

void CollisionComponent::checkCollision(std::vector<Entity*>& collidersVector)
{
	for (auto& otherEntity : collidersVector)
	{
		CollisionComponent* pOtherCC = &otherEntity->getComponent<CollisionComponent>();
		Rectangle2D otherCollisionBox;
		Circle2D otherCollisionCircle;
		bool collided = false;
		Vector2D collisionDirection = Vector2D(0, 0);
		if (pOtherCC->isActive() == true)
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
						if (pPC->getVelocity().YValue <= -129)
						{
							pSC->setSound("playerLand");
							pSC->play();
						}
						pPC->stableGround();
					}
				}
				if (colliderType == TrappedPlatform)
				{
					float trapAngle = otherEntity->getComponent<TransformComponent>().getRotation();
					if (trapAngle == 0)
					{
						if (collisionDirection == Vector2D(0, -1))
						{
							if (pPC->getVelocity().YValue <= -129)
							{
								pSC->setSound("playerLand");
								pSC->play();
							}
							pPC->stableGround();
						}
						if (collisionDirection == Vector2D(0, 1))
						{
							setActive(false);
							pGC->setLose(true);
						}
					}
					if (trapAngle == 3.142f)
					{
						if (collisionDirection == Vector2D(0, 1))
						{
							pPC->bounceBack();
						}
						if (collisionDirection == Vector2D(0, -1))
						{
							setActive(false);
							pGC->setLose(true);
						}
					}
					
				}
				if (colliderType == Trap)
				{
					setActive(false);
					pGC->setLose(true);
				}
				if (colliderType == DestroyedEdge)
				{
					setActive(false);
					pGC->setLose(true);
				}
				if (colliderType == Exit)
				{
					setActive(false);
					pGC->setWin(true);
				}
				if (colliderType == Point)
				{
					otherEntity->getComponent<CollisionComponent>().setActive(false);
					otherEntity->setWorldType(Empty);
					otherEntity->getComponent<TransformComponent>().addPosition(Vector2D(0, 16));
					otherEntity->getComponent<ImageComponent>().setImage("empty");

					pGC->increaseScore();
					pSC->setSound("playerPoint");
					pSC->play();
				}
			}
		}
	}
}

const char* CollisionComponent::getCollisionShape()
{
	return collisionShape;
}

Rectangle2D CollisionComponent::getCollisionBox()
{
	return collisionBox;
}

Circle2D CollisionComponent::getCollisionCircle()
{
	return collisionCircle;
}