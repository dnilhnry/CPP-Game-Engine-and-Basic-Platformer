#pragma once

#include "Components.h"
#include "mysoundengine.h"
#include "AssetManager.h"

class SoundComponent : public Component
{
private:
	MySoundEngine* pSE;
	AssetManager* pAM;

	EntityType entityType;
	
	SoundIndex sound;
	bool looping;

public:
	SoundComponent(MySoundEngine* se, AssetManager* am)
	{
		pSE = se;
		pAM = am;
	}

	void init() override
	{
		entityType = entity->getEntityType();
		looping = false;
	}

	void setSound(const char* s);
	void setSound(const char* s, bool l);

	void play();

};