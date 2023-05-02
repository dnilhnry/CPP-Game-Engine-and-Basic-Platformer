#pragma once

#include "Components.h"
#include "mysoundengine.h"
#include "AssetManager.h"
#include "EntityTypes.h"

class SoundComponent : public Component
{
private:
	MySoundEngine* pSE;
	AssetManager* pAM;

	EntityType entityType;
	
	SoundIndex sound;
	bool looping;

public:
	SoundComponent(MySoundEngine* se, AssetManager* am, EntityType type)
	{
		pSE = se;
		pAM = am;
		EntityType entityType = type;
	}

	void setSound(const char* s, bool l)
	{
		switch (entityType)
		{
		case Character:
			sound = pAM->GetCharacterSound(s);
			break;
		case Background:
			sound = pAM->GetBackgroundSound(s);
			break;
		case World:
			sound = pAM->GetWorldSound(s);
			break;
		default:
			break;
		}
		looping = l;
	}

	void init() override
	{
	}

	void update() override
	{
	}

	void play()
	{
		pSE->Play(sound, looping);
	}

};