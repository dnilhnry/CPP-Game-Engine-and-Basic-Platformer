#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "EntityTypes.h"


class Component;
class Entity;
class EntityManager;

using ComponentID = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;

using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
private:
	bool active = true;

public:
	Entity* entity;

	virtual ~Component() {}

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	bool isActive();
	void setActive(bool a);

};

class Entity
{
private:
	EntityManager& entityManager;
	bool active = true;
	int id;
	EntityType entityType;
	WorldType worldType;
	double frameTime;

	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitset componentBitset;

public:
	Entity(EntityManager& em, int i, EntityType et) : entityManager(em)
	{
		id = i;
		entityType = et;
		if (entityType != World)
		{
			worldType = NOTworld;
		}
	}

	Entity(EntityManager& em, int i, EntityType et, WorldType wt ) : entityManager(em)
	{
		id = i;
		entityType = et;
		worldType = wt;
	}

	void update();

	void updateTime(double time);

	void draw();

	bool isActive() const;

	void deleteEntity();

	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs &&...mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	int getID() const;

	EntityType getEntityType() const;

	void setWorldType(WorldType wt);

	WorldType getWorldType();

	double getGameTime();

};

class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update();

	void updateTime(double frameTime);

	void draw();

	void deleteAll();

	void refresh();

	Entity& addEntity(int i, EntityType et);
	Entity& addEntity(int i, EntityType et, WorldType wt);

	Entity& getEntity(int i);

	std::vector<std::unique_ptr<Entity>>& getAllEntities();

};