#pragma once

#include "Components.h"
#include "mysoundengine.h"

class SoundComponent : public Component
{
private:
	MySoundEngine* pSE;
	SoundIndex sound;

public:
	SoundComponent(MySoundEngine* se)
	{
		pSE = se;
	}

	void setSound(SoundIndex s)
	{
		sound = s;
	}

	void init() override
	{
	}

	void update() override
	{
	}

	void play()
	{
		pSE->Play(sound);
	}


};