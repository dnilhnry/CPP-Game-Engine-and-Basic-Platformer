#include "Components.h"

void ModifyComponent::toDestroyedEdge()
{
	if (entity->hasComponent<AnimationComponent>() == true)
	{
		entity->getComponent<AnimationComponent>().setActive(false);
		entity->getComponent<TransformComponent>().setRotation(0.0f);
	}
	entity->setWorldType(DestroyedEdge);
	pIC->setImage("destroyedEdge");
	pCC->setActive(true);
	Vector2D lbCorner = Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32);
	Vector2D rtCorner = Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 24);
	pCC->moveCollisionBox(lbCorner, rtCorner);
}

void ModifyComponent::toDestroyed()
{
	entity->setWorldType(Destroyed);
	pIC->setImage("destroyed");
	pCC->setActive(false);
}

void ModifyComponent::pointDestroyedEdge()
{
	entity->setWorldType(DestroyedEdge);
	pTC->addPosition(Vector2D(0, 16));
	pIC->setImage("destroyedEdge");
	pCC->setActive(true);
	Vector2D lbCorner = Vector2D(pTC->getPosition().XValue - 32, pTC->getPosition().YValue - 32);
	Vector2D rtCorner = Vector2D(pTC->getPosition().XValue + 32, pTC->getPosition().YValue + 24);
	pCC->moveCollisionBox(lbCorner, rtCorner);
}