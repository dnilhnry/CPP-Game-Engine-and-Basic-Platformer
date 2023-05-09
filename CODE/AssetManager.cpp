#include "AssetManager.h"

void AssetManager::LoadCharacterImage(const wchar_t* path, const char* name)
{
	characterImagesMap.insert({ name,pDE->LoadPicture(path) });
}

PictureIndex AssetManager::GetCharacterImage(const char* name)
{
	return characterImagesMap.at(name);
}

void AssetManager::LoadCharacterSound(const wchar_t* path, const char* name)
{
	characterSoundsMap.insert({ name,pSE->LoadWav(path) });
}

SoundIndex AssetManager::GetCharacterSound(const char* name)
{
	return characterSoundsMap.at(name);
}

void AssetManager::LoadBackgroundImage(const wchar_t* path, const char* name)
{
	backgroundImagesMap.insert({ name,pDE->LoadPicture(path) });
}

PictureIndex AssetManager::GetBackgroundImage(const char* name)
{
	return backgroundImagesMap.at(name);
}

void AssetManager::LoadBackgroundSound(const wchar_t* path, const char* name)
{
	backgroundSoundMap.insert({ name,pSE->LoadWav(path) });
}

SoundIndex AssetManager::GetBackgroundSound(const char* name)
{
	return backgroundSoundMap.at(name);
}

void AssetManager::LoadWorldImage(const wchar_t* path, const char* name)
{
	worldImagesMap.insert({ name,pDE->LoadPicture(path) });
}

PictureIndex AssetManager::GetWorldImage(const char* name)
{
	return worldImagesMap.at(name);
}

void AssetManager::LoadWorldSound(const wchar_t* path, const char* name)
{
	worldSoundsMap.insert({ name,pSE->LoadWav(path) });
}

SoundIndex AssetManager::GetWorldSound(const char* name)
{
	return worldSoundsMap.at(name);
}

void AssetManager::loadAll()
{
	LoadCharacterImage(L"assets/character/image/smiley.png", "playerSmiley");
	LoadCharacterImage(L"assets/character/image/scared.png", "playerScared");
	LoadCharacterImage(L"assets/character/image/confused.png", "playerConfused");
	LoadCharacterImage(L"assets/character/image/dead.png", "playerDead");

	LoadCharacterSound(L"assets/character/sound/land.wav", "playerLand");
	LoadCharacterSound(L"assets/character/sound/point.wav", "playerPoint");
	LoadCharacterSound(L"assets/character/sound/win.wav", "playerWin");
	LoadCharacterSound(L"assets/character/sound/death.wav", "playerDeath");

	LoadBackgroundImage(L"assets/background/image/768576darkblue.png", "backgroundImage");

	// LoadBackgroundMusic(L"assets/background/music/level0.wav", "backgroundMusic");

	LoadWorldImage(L"assets/world/image/platform.png", "platform");
	LoadWorldImage(L"assets/world/image/trappedPlatform.png", "trappedPlatform");
	LoadWorldImage(L"assets/world/image/trap.png", "trap");
	LoadWorldImage(L"assets/world/image/destroyed.png", "destroyed");
	LoadWorldImage(L"assets/world/image/destroyedEdge.png", "destroyedEdge");
	LoadWorldImage(L"assets/world/image/exit.png", "exit");
	LoadWorldImage(L"assets/world/image/point.png", "point");

	// LoadWorldSound(L"assets/world/image/TODO.wav", "TODO");
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