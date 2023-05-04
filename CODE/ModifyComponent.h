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

	// time variables to control speed to level destruction
	double frameTime;


public:
	ModifyComponent(int r)
	{
		rowNumber = r;
	}

	void init() override
	{
		entityType = entity->getEntityType();
		worldType = entity->getWorldType();
		pTC = &entity->getComponent<TransformComponent>();
		pIC = &entity->getComponent<ImageComponent>();
		pCC = &entity->getComponent<CollisionComponent>();
	}

	void update(double ft) override
	{
		// use time variables to control speed to level destruction
		frameTime = ft;
	}

	void toDestroyedEdge()
	{
		entity->setWorldType(DestroyedEdge);
		Vector2D position = pTC->getPosition();
		pIC->setImage("destroyedEdge");
		// pCC->setCollision();
	}

	void toDestroyed()
	{
		entity->setWorldType(Destroyed);
		Vector2D position = pTC->getPosition();
		pIC->setImage("destroyed");
		// pCC->setCollision();
	}

	void pointEmpty()
	{
		entity->setWorldType(Empty);
		Vector2D position = pTC->getPosition();
		pTC->setPosition(Vector2D(position.XValue,position.YValue + 16));
		pIC->setImage("empty");
		// pCC->setCollision();
	}

	void pointDestroyedEdge()
	{
		entity->setWorldType(DestroyedEdge);
		Vector2D position = pTC->getPosition();
		pTC->setPosition(Vector2D(position.XValue, position.YValue + 16));
		pIC->setImage("destroyedEdge");
		// pCC->setCollision();
	}

};