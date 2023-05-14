/*

Level Manager

This class is used to load a level from a text file and create the level in the game world.
the level is selected from the level menu
the selected level is passed to the init method which sets the level file to be loaded
the loadLevel method is passed a pointer to the entity manager, draw engine and asset manager
The level is parsed from a text file and the required entites are created using the EntityManager class.
all of the entities also have their components added and initialised.

*/

#pragma once

#include <unordered_map>

#include "Levels.h"
#include "vector2D.h"

class Entity;
class EntityManager;
class MyDrawEngine;
class AssetManager;

class LevelManager
{
private:
	Levels selectedLevel;
	const char* levelFile;
	Vector2D startPosition = Vector2D(-352,1688);
	int tileSize = 64;
	int LevelWidth = 12;
	int LevelHeight = 30;
	std::unordered_map<int, std::vector<Entity*>> collidersMap;

public:

	// init method sets the level file to be loaded
	void init(Levels l);

	// loadLevel method loads the level from the text file and creates the entities in the game world
	void loadLevel(EntityManager* pEM, MyDrawEngine* pDE, AssetManager* pAM);

	// gets a map of the colliders vectors of entities
	std::unordered_map<int, std::vector<Entity*>> getCollidersMap();

};