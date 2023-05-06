#pragma once

#include "Levels.h"
#include "vector2D.h"

class EntityManager;
class MyDrawEngine;
class AssetManager;

class LevelManager
{
private:
	Levels currentLevel;
	const char* levelFile;
	Vector2D startPosition = Vector2D(-352,1688);
	int tileSize = 64;
	int LevelWidth = 12;
	int LevelHeight = 30;

public:

	void init(Levels l);

	void loadLevel(EntityManager* pEM, MyDrawEngine* pDE, AssetManager* pAM);

};