#include "Components.h"

void CollisionComponent::checkCollision(std::vector<Entity*>& collidersVector)
{
	for (auto& otherEntity : collidersVector)
	{
		CollisionComponent* pOtherCC = &otherEntity->getComponent<CollisionComponent>();
		bool collided = false;
		Vector2D collisionDirection = Vector2D(0, 0);
		if (pOtherCC->isActive() == true && pOtherCC->ignoreTime <= 0)
		{
			Rectangle2D otherCollisionBox = pOtherCC->getCollisionBox();
			if (collisionCircle.Intersects(otherCollisionBox) == true)
			{
				collisionDirection = otherCollisionBox.CollisionNormal(collisionCircle);
				collided = true;
			}


			if (collided == true)
			{
				WorldType colliderType = otherEntity->getWorldType();
				if (colliderType == Platform)
				{
					if ((collisionDirection.XValue <= leftBoundary && collisionDirection.XValue >= rightBoundary) && collisionDirection.YValue >= lowerBoundary)
					{
						if (pPC->getVelocity().YValue <= -255)
						{
							pSC->setSound("playerLand");
							pSC->play();
						}
						pPC->stableGround();
					}
					if (collisionDirection.YValue < lowerBoundary && collisionDirection.YValue > upperBoundary)
					{
						if (collisionCircle.Intersection(otherCollisionBox).XValue < otherCollisionBox.GetCentre().XValue)
						{
							pTC->addPosition(Vector2D(collisionCircle.Intersection(otherCollisionBox).XValue - (otherCollisionBox.GetCentre().XValue - 32), 0));
						}
						if (collisionCircle.Intersection(otherCollisionBox).XValue > otherCollisionBox.GetCentre().XValue)
						{
							pTC->addPosition(Vector2D(collisionCircle.Intersection(otherCollisionBox).XValue - (otherCollisionBox.GetCentre().XValue + 32), 0));
						}
					}
					if ((collisionDirection.XValue <= leftBoundary && collisionDirection.XValue >= rightBoundary) && collisionDirection.YValue <= upperBoundary)
					{
						pOtherCC->ignoreTime = 1.0;
					}
				}
				if (colliderType == TrappedPlatform)
				{
					float trapAngle = otherEntity->getComponent<TransformComponent>().getRotation();
					if (trapAngle == 0)
					{
						if (collisionDirection.XValue <= leftBoundary && collisionDirection.XValue >= rightBoundary && collisionDirection.YValue >= lowerBoundary)
						{
							if (pPC->getVelocity().YValue <= -255)
							{
								pSC->setSound("playerLand");
								pSC->play();
							}
							pPC->stableGround();
						}
						if (collisionDirection.XValue > leftBoundary || collisionDirection.XValue < rightBoundary || collisionDirection.YValue <= upperBoundary)
						{
							setActive(false);
							pGC->setLose(true);
						}
					}
					if (trapAngle == 3.142f)
					{
						if (collisionDirection.XValue > leftBoundary || collisionDirection.XValue < rightBoundary || collisionDirection.YValue <= upperBoundary)
						{
							pPC->bounceBack();
						}
						if (collisionDirection.XValue <= leftBoundary && collisionDirection.XValue >= rightBoundary && collisionDirection.YValue >= lowerBoundary)
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

Rectangle2D CollisionComponent::getCollisionBox()
{
	return collisionBox;
}

void CollisionComponent::moveCollisionBox(Vector2D newLB, Vector2D newRT)
{
	collisionBox.PlaceAt(newLB, newRT);
}