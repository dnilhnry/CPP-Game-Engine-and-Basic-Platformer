/*

Entity Component System

Entity Manager
The entity manager is responsible for managing all entities in the game.
It has a vector of unique pointers to entities.
It can be used to easily add new entities to the game, update all entities
and delete all entities during runtime and clean up

Entity
An entity is a game object.
every entity has an id, an entity type and a world type.
these variables are used to identify the entity.
every entity has a vector of unique pointers to components.
every entity has a component array and a component bitset.
the component array is used to store pointers to components.
the component bitset is used to check if an entity has a certain component.
every entity has a method to add a component to the entity.
every entity has a method to get a component from the entity.
every entity has a method to check if the entity has a certain component.
every entity has a method to update each of the components in the entity.
every entity has a method to delete the entity.

Component
A component is a part of an entity.
every component has a pointer to the entity it belongs to.
every component has a virtual method to initialise the component.
every component has a virtual method to update the component.
the virtual methods are overridden by the created components.
every component has a method to check if the component is active.
every component has a method to set the component active or inactive.


An example:

Entity manager
	- Entity 1 (Player)
		- Component 1 (Transform)
		- Component 2 (image)
		- Component 3 (sound)
		- more...
	- Entity 2 (background)
		- Component 2 (image)
		- Component 3 (sound)
	- Entity 3 (Platform)
		- Component 1 (transform)
		- Component 2 (image)

*/

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

// returns a unique component id
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

// returns a component type id based on the component class
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitset = std::bitset<maxComponents>;

using ComponentArray = std::array<Component*, maxComponents>;


// Generic Component Class - All Components inherit from this
class Component
{
private:
	bool active = true;

public:
	Entity* entity;

	virtual ~Component() {}

	// virtual methods to be overridden by components
	// init() is called when the component is added to an entity
	virtual void init() {}

	// virtual methods to be overridden by components
	// update() is called every frame
	virtual void update() {}

	// returns true if the component is active
	bool isActive();

	// sets the component active or inactive
	void setActive(bool a);

};

// Entity Class - All game objects are entities
// Entities are made up of components
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
	// constructor - takes an entity manager, an id and an entity type
	// world type is set to NOTworld
	Entity(EntityManager& em, int i, EntityType et) : entityManager(em)
	{
		id = i;
		entityType = et;
		if (entityType != World)
		{
			worldType = NOTworld;
		}
	}

	// constructor - takes an entity manager, an id, an entity type and a world type
	Entity(EntityManager& em, int i, EntityType et, WorldType wt ) : entityManager(em)
	{
		id = i;
		entityType = et;
		worldType = wt;
	}

	// update all components in the entity
	void update();

	// updates the frame time of the entity
	void updateTime(double time);

	// returns true if the entity is active
	bool isActive() const;

	// sets the entity inactive
	void deleteEntity();

	// returns true if the entity has a certain component
	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	// adds a component to the entity
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

	// gets a component pointer from the entity
	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	// returns the entity id
	int getID() const;

	// returns the entity type
	EntityType getEntityType() const;

	// changes the world type
	void setWorldType(WorldType wt);

	// returns the world type
	WorldType getWorldType();

	// returns the frame time
	double getGameTime();

};

// Entity Manager Class - Manages all entities in the game
class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	// update all entities
	// updates each component of each entity
	void update();

	// update the frame time of all entities
	void updateTime(double frameTime);

	// sets every entity inactive
	void deleteAll();

	// deletes all inactive entities
	void refresh();

	// adds an entity to the entity manager
	Entity& addEntity(int i, EntityType et);

	// adds an entity to the entity manager
	Entity& addEntity(int i, EntityType et, WorldType wt);

	// returns an entity from the entity manager - uses the entity id
	Entity& getEntity(int i);

	// returns a vector of all entities
	std::vector<std::unique_ptr<Entity>>& getAllEntities();

};