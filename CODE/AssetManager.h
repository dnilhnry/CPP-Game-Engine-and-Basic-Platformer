/*

AssetManager

this class is used to load and retrieve all the assets used in the game
this class integrates the MyDrawEngine and MySoundEngine classes
the picture and sound indexes are stored in unordered maps with the name of the asset as the key
the key is used to retrieve the index of the asset

*/

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
	~AssetManager() { clearAll(); }

	// This method is used to initialise the asset manager
	// it is used to set the MyDrawEngine and MySoundEngine pointers
	// empty values are added to the maps so entities can display nothing if they need to
	void init(MyDrawEngine* de, MySoundEngine* se)
	{
		pDE = de;
		pSE = se;
		characterImagesMap.insert({ "empty", -1 });
		characterSoundsMap.insert({ "empty", -1 });
		backgroundImagesMap.insert({ "empty", -1 });
		backgroundSoundMap.insert({ "empty", -1 });
		worldImagesMap.insert({ "empty", -1 });
		worldSoundsMap.insert({ "empty", -1 });
	}

	// This method is used to load a picture for a character entity
	void loadCharacterImage(const wchar_t* path, const char* name);

	// This method is used to retrieve the index of a picture for a character entity
	PictureIndex getCharacterImage(const char* name);

	// This method is used to load a sound for a character entity
	void loadCharacterSound(const wchar_t* path, const char* name);

	// This method is used to retrieve the index of a sound for a character entity
	SoundIndex getCharacterSound(const char* name);

	// This method is used to load a picture for a background entity
	void loadBackgroundImage(const wchar_t* path, const char* name);

	// This method is used to retrieve the index of a picture for a background entity
	PictureIndex getBackgroundImage(const char* name);

	// This method is used to load a sound for a background entity
	void loadBackgroundSound(const wchar_t* path, const char* name);

	// This method is used to retrieve the index of a sound for a background entity
	SoundIndex getBackgroundSound(const char* name);

	// This method is used to load a picture for a world entity
	void loadWorldImage(const wchar_t* path, const char* name);

	// This method is used to retrieve the index of a picture for a world entity
	PictureIndex getWorldImage(const char* name);

	// This method is used to load a sound for a world entity
	void loadWorldSound(const wchar_t* path, const char* name);

	// This method is used to retrieve the index of a sound for a world entity
	SoundIndex getWorldSound(const char* name);

	// This method is used to load every required asset
	void loadAll();

	// This method is used to clear the asset maps
	void clearAll();

};