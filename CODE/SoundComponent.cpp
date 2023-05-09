#include "Components.h"

void SoundComponent::setSound(const char* s)
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
	playing = false;
	looping = false;
}

void SoundComponent::setSound(const char* s, bool l)
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
	playing = false;
	looping = l;
}

void SoundComponent::play()
{
	if (playing == false)
	{
		if (sound != -1 && sound != NULL)
		{
			pSE->Play(sound, looping);
			playing = true;
		}
	}
}