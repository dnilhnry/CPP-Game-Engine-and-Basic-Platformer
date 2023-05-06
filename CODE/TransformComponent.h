#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	Vector2D position;
	float angle;
	float scale;

public:

	TransformComponent(Vector2D p, float a, float s)
	{
		position = p;
		angle = a;
		scale = s;
	}

	Vector2D getPosition();

	void setPosition(Vector2D newPosition);

	void addPosition(Vector2D newPosition);

	float getRotation();

	void setRotation(float newAngle);

	void addRotation(float newAngle);

	float getScale();

	void setScale(float newScale);

	void addScale(float newScale);

};