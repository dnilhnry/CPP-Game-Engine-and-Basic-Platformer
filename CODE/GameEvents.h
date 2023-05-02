#pragma once

#include "AssetManager.h"
#include "Components.h"

class GameEvents
{
private:
	AssetManager* assetManager;
	Manager* entityManager;

public:
	GameEvents(AssetManager* am, Manager* em)
	{
		assetManager = am;
		entityManager = em;
	}

	void LoadAssets();
};