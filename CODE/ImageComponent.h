#pragma once

#include "Components.h"
#include "mydrawengine.h"
#include "vector2D.h"

class ImageComponent : public Component
{
private:
	MyDrawEngine* pDE;
	PictureIndex image;
	TransformComponent* transformComponent;
	Vector2D position;
	float angle;
	float scale;
	float transparency = 1;

public:

	ImageComponent(const wchar_t* path)
	{
		setImage(path);
	}

	void setImage(const wchar_t* path)
	{
		image = pDE->LoadPicture(path);
	}

	void init() override
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		transformComponent = &entity->getComponent<TransformComponent>();
		position = transformComponent->getPosition();
		angle = transformComponent->getRotation();
		scale = transformComponent->getScale();
	}

	void update() override
	{
		position = transformComponent->getPosition();
		angle = transformComponent->getRotation();
		scale = transformComponent->getScale();
	}

	void draw() override
	{
		pDE->DrawAt(position, image, scale, angle, transparency);
	}


};