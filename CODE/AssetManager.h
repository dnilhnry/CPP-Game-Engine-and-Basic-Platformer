#pragma once

#include <unordered_map>

#include "mydrawengine.h"
#include "mysoundengine.h"

class AssetManager
{
private:
	MyDrawEngine* pDE;
	MySoundEngine* pSE;

	std::unordered_map<const char*, PictureIndex> characterImagesMap;
	std::unordered_map<const char*, SoundIndex> characterSoundsMap;
	std::unordered_map<const char*, PictureIndex> backgroundImagesMap;
	std::unordered_map<const char*, SoundIndex> backgroundSoundMap;
	std::unordered_map<const char*, PictureIndex> worldImagesMap;
	std::unordered_map<const char*, SoundIndex> worldSoundsMap;

public:
	AssetManager() {}
	~AssetManager() {}

	void init(MyDrawEngine* de, MySoundEngine* se)
	{
		pDE = de;
		pSE = se;
	}

	void LoadCharacterImage(const wchar_t* path, const char* name);

	PictureIndex GetCharacterImage(const char* name);

	void LoadCharacterSound(const wchar_t* path, const char* name);

	SoundIndex GetCharacterSound(const char* name);

	void LoadBackgroundImage(const wchar_t* path, const char* name);

	PictureIndex GetBackgroundImage(const char* name);

	void LoadBackgroundSound(const wchar_t* path, const char* name);

	SoundIndex GetBackgroundSound(const char* name);

	void LoadWorldImage(const wchar_t* path, const char* name);

	PictureIndex GetWorldImage(const char* name);

	void LoadWorldSound(const wchar_t* path, const char* name);

	SoundIndex GetWorldSound(const char* name);

};