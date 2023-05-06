#pragma once

#include "Components.h"
#include "mydrawengine.h"
#include "AssetManager.h"
#include "vector2D.h"

class ImageComponent : public Component
{
private:
	MyDrawEngine* pDE;
	AssetManager* pAM;
	TransformComponent* pTC;

	EntityType entityType;

	Vector2D position;
	PictureIndex image;
	float angle;
	float scale;
	float transparency;

public:
	ImageComponent(MyDrawEngine* de, AssetManager* am)
	{
		pDE = de;
		pAM = am;
	}

	void init() override
	{
		entityType = entity->getEntityType();
		pTC = &entity->getComponent<TransformComponent>();
		position = pTC->getPosition();
		angle = pTC->getRotation();
		scale = pTC->getScale();
		transparency = 0.0f;
	}

	void update() override
	{
		position = pTC->getPosition();
		angle = pTC->getRotation();
		scale = pTC->getScale();
	}

	void setImage(const char* i);

	void draw();

};