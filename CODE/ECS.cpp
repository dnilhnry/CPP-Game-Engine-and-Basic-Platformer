#include "Components.h"

// Component
//--------------------------------------------------------------

bool Component::isActive()
{
	return active;
}

void Component::setActive(bool a)
{
	active = a;
}

//--------------------------------------------------------------

// Entity
//--------------------------------------------------------------

void Entity::update()
{
	for (auto& c : components) { c->update(); }
}

void Entity::updateTime(double time)
{
	frameTime = time;
}

bool Entity::isActive() const
{
	return active;
}

void Entity::deleteEntity()
{
	active = false;
}

int Entity::getID() const
{
	return id;
}

EntityType Entity::getEntityType() const
{
	return entityType;
}

void Entity::setWorldType(WorldType wt)
{
	worldType = wt;
}

WorldType Entity::getWorldType()
{
	return worldType;
}

double Entity::getGameTime()
{
	return frameTime;
}

//--------------------------------------------------------------

// EntityManager
//--------------------------------------------------------------

void EntityManager::update()
{
	for (auto& e : entities)
	{
		e->update();
	}
}

void EntityManager::updateTime(double frameTime)
{
	for (auto& e : entities)
	{
		e->updateTime(frameTime);
	}
}

void EntityManager::deleteAll()
{
	for (auto& e : entities)
	{
		e->deleteEntity();
	}
}

void EntityManager::removeInactiveEntities()
{
	entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& e)
		{ return !e->isActive(); }
	), std::end(entities));
}

Entity& EntityManager::addEntity(int i, EntityType et)
{
	Entity* e = new Entity(*this, i, et);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}

Entity& EntityManager::addEntity(int i, EntityType et, WorldType wt)
{
	Entity* e = new Entity(*this, i, et, wt);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}

Entity& EntityManager::getEntity(int i)
{
	for (auto& e : entities)
	{
		if (e->getID() == i)
		{
			return *e;
		}
	}
}

std::vector<std::unique_ptr<Entity>>& EntityManager::getAllEntities()
{
	return entities;
}

//--------------------------------------------------------------