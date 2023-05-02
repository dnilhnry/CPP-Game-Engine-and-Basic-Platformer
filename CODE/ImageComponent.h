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
	float transparency;

public:

	ImageComponent(MyDrawEngine* de)
	{
		pDE = de;
	}

	/*void setImage(const wchar_t* path)
	{
		image = pDE->LoadPicture(path);
	}*/

	void setImage(PictureIndex i)
	{
		image = i;
	}

	void init() override
	{
		MyDrawEngine* pDE = MyDrawEngine::GetInstance();
		transformComponent = &entity->getComponent<TransformComponent>();
		position = transformComponent->getPosition();
		angle = transformComponent->getRotation();
		scale = transformComponent->getScale();
		transparency = 0.0f;
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