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

	Vector2D getPosition()
	{
		return position;
	}

	void setPosition(Vector2D newPosition)
	{
		position = newPosition;
	}

	void addPosition(Vector2D newPosition)
	{
		position = position + newPosition;
	}

	float getRotation()
	{
		return angle;
	}

	void setRotation(float newAngle)
	{
		angle = newAngle;
	}

	void addRotation(float newAngle)
	{
		angle = angle + newAngle;
	}

	float getScale()
	{
		return scale;
	}

	void setScale(float newScale)
	{
		scale = newScale;
	}

	void addScale(float newScale)
	{
		scale = scale + newScale;
	}

};