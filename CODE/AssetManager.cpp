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