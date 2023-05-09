/*

The sound component is used to play a wave file
it should be added by all entities that have an audible representation
this component uses the asset manager to get the sound to play
the play method uses the MySoundEnginge to play the sound

*/

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
	bool playing;
	bool looping;

public:
	// constructor - sets the pointer to the sound engine and the asset manager
	SoundComponent(MySoundEngine* se, AssetManager* am)
	{
		pSE = se;
		pAM = am;
	}

	// init - sets the entity type and looping to false
	void init() override
	{
		entityType = entity->getEntityType();
		playing = false;
		looping = false;
	}

	// sets the sound to play - looping is set to false
	void setSound(const char* s);

	// sets the sound to play and whether it should loop
	void setSound(const char* s, bool l);

	// plays the sound
	void play();

};