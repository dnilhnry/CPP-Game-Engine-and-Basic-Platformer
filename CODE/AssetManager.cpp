#include "AssetManager.h"

void AssetManager::loadCharacterImage(const wchar_t* path, const char* name)
{
	characterImagesMap.insert({ name,pDE->LoadPicture(path) });
}

PictureIndex AssetManager::getCharacterImage(const char* name)
{
	return characterImagesMap.at(name);
}

void AssetManager::loadCharacterSound(const wchar_t* path, const char* name)
{
	characterSoundsMap.insert({ name,pSE->LoadWav(path) });
}

SoundIndex AssetManager::getCharacterSound(const char* name)
{
	return characterSoundsMap.at(name);
}

void AssetManager::loadBackgroundImage(const wchar_t* path, const char* name)
{
	backgroundImagesMap.insert({ name,pDE->LoadPicture(path) });
}

PictureIndex AssetManager::getBackgroundImage(const char* name)
{
	return backgroundImagesMap.at(name);
}

void AssetManager::loadBackgroundSound(const wchar_t* path, const char* name)
{
	backgroundSoundMap.insert({ name,pSE->LoadWav(path) });
}

SoundIndex AssetManager::getBackgroundSound(const char* name)
{
	return backgroundSoundMap.at(name);
}

void AssetManager::loadWorldImage(const wchar_t* path, const char* name)
{
	worldImagesMap.insert({ name,pDE->LoadPicture(path) });
}

PictureIndex AssetManager::getWorldImage(const char* name)
{
	return worldImagesMap.at(name);
}

void AssetManager::loadWorldSound(const wchar_t* path, const char* name)
{
	worldSoundsMap.insert({ name,pSE->LoadWav(path) });
}

SoundIndex AssetManager::getWorldSound(const char* name)
{
	return worldSoundsMap.at(name);
}

void AssetManager::loadAll()
{
	loadCharacterImage(L"assets/character/image/smiley.png", "playerSmiley");
	loadCharacterImage(L"assets/character/image/scared.png", "playerScared");
	loadCharacterImage(L"assets/character/image/confused.png", "playerConfused");
	loadCharacterImage(L"assets/character/image/dead.png", "playerDead");

	loadCharacterSound(L"assets/character/sound/land.wav", "playerLand");
	loadCharacterSound(L"assets/character/sound/point.wav", "playerPoint");
	loadCharacterSound(L"assets/character/sound/win.wav", "playerWin");
	loadCharacterSound(L"assets/character/sound/death.wav", "playerDeath");

	loadBackgroundImage(L"assets/background/image/768576darkblue.png", "backgroundImage");

	loadBackgroundSound(L"assets/background/sound/backgroundMusic.wav", "backgroundMusic");

	loadWorldImage(L"assets/world/image/platform.png", "platform");
	loadWorldImage(L"assets/world/image/trappedPlatform.png", "trappedPlatform");
	loadWorldImage(L"assets/world/image/trap.png", "trap");
	loadWorldImage(L"assets/world/image/destroyed.png", "destroyed");
	loadWorldImage(L"assets/world/image/destroyedEdge.png", "destroyedEdge");
	loadWorldImage(L"assets/world/image/exit.png", "exit");
	loadWorldImage(L"assets/world/image/point.png", "point");

	// loadWorldSound(L"assets/world/image/TODO.wav", "TODO");
}

void AssetManager::clearAll()
{
	characterImagesMap.clear();
	characterSoundsMap.clear();
	backgroundImagesMap.clear();
	backgroundSoundMap.clear();
	worldImagesMap.clear();
	worldSoundsMap.clear();
}