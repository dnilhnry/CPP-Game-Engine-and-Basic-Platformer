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

	void setSound(const char* s)
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
		looping = false;
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
		entityType = entity->getEntityType();
		looping = false;
	}

	void update() override
	{
	}

	void play()
	{
		if (sound != -1 && sound != NULL)
		{
			pSE->Play(sound, looping);
		}
	}

};