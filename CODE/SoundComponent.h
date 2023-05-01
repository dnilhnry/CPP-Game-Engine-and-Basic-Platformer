#pragma once

#include "Components.h"
#include "mysoundengine.h"

class SoundComponent : public Component
{
private:
	MySoundEngine* pSE;
	SoundIndex sound;

public:
	SoundComponent() = default;

	SoundComponent(const wchar_t* path)
	{
		setSound(path);
	}

	void setSound(const wchar_t* path)
	{
		sound = pSE->LoadWav(path);
	}

	void init() override
	{
		MySoundEngine* pSE = MySoundEngine::GetInstance();
	}

	void update() override
	{
	}

	void play()
	{
		pSE->Play(sound);
	}


};