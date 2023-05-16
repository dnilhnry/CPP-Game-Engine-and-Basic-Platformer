#include "Components.h"

void CollisionComponent::checkCollision(std::vector<Entity*>& collidersVector)
{
	for (auto& otherEntity : collidersVector)
	{

		bool collided = false;
		Vector2D collisionDirection = Vector2D(0, 0);


		CollisionComponent* pOtherCC = &otherEntity->getComponent<CollisionComponent>();
		
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
					// player collides with the top of the platform
					if (collisionDirection.YValue >= lowerBoundary)
					{
						// if the player is falling at high speed, the player makes a noise when landing
						if (pPC->getVelocity().YValue <= -255)
						{
							pSC->setSound("playerLand");
							pSC->play();
						}

						// physics component is updated to enable player jumping and avoid falling through the platform
						pPC->stableGround();

						// ensures player is not stuck in the platform
						if (collisionCircle.GetCentre().XValue >= (otherCollisionBox.GetCentre().XValue - 32) && collisionCircle.GetCentre().XValue <= (otherCollisionBox.GetCentre().XValue + 32))
						{
							if ((collisionCircle.GetCentre().YValue - 30) < (otherCollisionBox.GetCentre().YValue + 8))
							{
								float displacement = (collisionCircle.GetCentre().YValue - 30) - (otherCollisionBox.GetCentre().YValue + 8);
								pTC->addPosition(Vector2D(0, -displacement));
							}
						}
					}
					// player collides with the edge of the platform
					if (collisionDirection.YValue >= upperBoundary && collisionDirection.YValue < lowerBoundary)
					{
						if (collisionCircle.Intersection(otherCollisionBox).XValue < otherCollisionBox.GetCentre().XValue)
						{
							float displacement = collisionCircle.Intersection(otherCollisionBox).XValue - (otherCollisionBox.GetCentre().XValue - 36);
							pTC->addPosition(Vector2D(-displacement, 0));
						}
						if (collisionCircle.Intersection(otherCollisionBox).XValue > otherCollisionBox.GetCentre().XValue)
						{
							float displacement = collisionCircle.Intersection(otherCollisionBox).XValue - (otherCollisionBox.GetCentre().XValue + 36);
							pTC->addPosition(Vector2D(-displacement, 0));
						}
					}
					// player collides with the bottom of the platform
					if (collisionDirection.YValue < upperBoundary)
					{
						pOtherCC->ignoreTime = 1.0;
					}
				}

				if (colliderType == TrappedPlatform)
				{
					float trapAngle = otherEntity->getComponent<TransformComponent>().getRotation();
					if (trapAngle == 0)
					{
						// player collides with the top of the platform (spikes on bottom)
						if(collisionDirection.YValue >= lowerBoundary)
						{
							// if the player is falling at high speed, the player makes a noise when landing
							if (pPC->getVelocity().YValue <= -255)
							{
								pSC->setSound("playerLand");
								pSC->play();
							}

							// physics component is updated to enable player jumping and avoid falling through the platform
							pPC->stableGround();

							// ensures player is not stuck in the platform
							if (collisionCircle.GetCentre().XValue >= (otherCollisionBox.GetCentre().XValue - 32) && collisionCircle.GetCentre().XValue <= (otherCollisionBox.GetCentre().XValue + 32))
							{
								if ((collisionCircle.GetCentre().YValue - 30) < (otherCollisionBox.GetCentre().YValue + 8))
								{
									float displacement = (collisionCircle.GetCentre().YValue - 30) - (otherCollisionBox.GetCentre().YValue + 8);
									pTC->addPosition(Vector2D(0, -displacement));
								}
							}
						}
						// player collides with the edge of the platform
						if (collisionDirection.YValue >= upperBoundary && collisionDirection.YValue < lowerBoundary)
						{
							if (collisionCircle.Intersection(otherCollisionBox).XValue < otherCollisionBox.GetCentre().XValue)
							{
								float displacement = collisionCircle.Intersection(otherCollisionBox).XValue - (otherCollisionBox.GetCentre().XValue - 36);
								pTC->addPosition(Vector2D(-displacement, 0));
							}
							if (collisionCircle.Intersection(otherCollisionBox).XValue > otherCollisionBox.GetCentre().XValue)
							{
								float displacement = collisionCircle.Intersection(otherCollisionBox).XValue - (otherCollisionBox.GetCentre().XValue + 36);
								pTC->addPosition(Vector2D(-displacement, 0));
							}
						}
						// player collides with the bottom of the platform
						if (collisionDirection.YValue < upperBoundary)
						{
							setActive(false);
							pGC->setLose(true);
						}
					}
					if (trapAngle == 3.142f)
					{
						// player collides with the bottom of the platform (spikes on top)
						if (collisionDirection.YValue < 1)
						{
							// player cannot pass through the platform so the player is bounced back down
							pPC->bounceBack();
						}
						// player collides with the bottom of the platform
						if (collisionDirection.YValue >= 1)
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
					// point is collected and entity is changed to empty version

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