/*

The image component is used to draw an image to the screen
it should be added by all entities that have a visual representation
this component uses the asset manager to get the image to draw
the draw method uses the MyDrawEnginge to draw the image

*/

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
	// constructor - sets the draw engine and asset manager pointers
	ImageComponent(MyDrawEngine* de, AssetManager* am)
	{
		pDE = de;
		pAM = am;
	}

	// initialise the component
	// sets the required variables
	void init() override
	{
		entityType = entity->getEntityType();
		pTC = &entity->getComponent<TransformComponent>();
		position = pTC->getPosition();
		angle = pTC->getRotation();
		scale = pTC->getScale();
		transparency = 0.0f;
	}

	// update the position, angle and scale of the image
	void update() override
	{
		position = pTC->getPosition();
		angle = pTC->getRotation();
		scale = pTC->getScale();
	}

	// sets the image to be drawn
	void setImage(const char* i);

	// if the component is active, draw the image
	void draw();

};