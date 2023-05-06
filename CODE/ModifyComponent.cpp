#include "Components.h"

void ModifyComponent::toDestroyedEdge()
{
	if (entity->hasComponent<AnimationComponent>() == true)
	{
		entity->getComponent<AnimationComponent>().setActive(false);
		entity->getComponent<TransformComponent>().setRotation(0.0f);
	}
	entity->setWorldType(DestroyedEdge);
	Vector2D position = pTC->getPosition();
	pIC->setImage("destroyedEdge");
	pCC->setActive(true);
}

void ModifyComponent::toDestroyed()
{
	entity->setWorldType(Destroyed);
	Vector2D position = pTC->getPosition();
	pIC->setImage("destroyed");
	pCC->setActive(false);
}

void ModifyComponent::pointDestroyedEdge()
{
	entity->setWorldType(DestroyedEdge);
	pTC->addPosition(Vector2D(0, 16));
	pIC->setImage("destroyedEdge");
	pCC->setActive(true);
}