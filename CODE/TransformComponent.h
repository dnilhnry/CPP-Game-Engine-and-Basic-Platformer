/*

The TransformComponent class is used to store the position, rotation and scale of an entity.
it is used by many other components to determine where the entity is and how it should be drawn.
The physics and collision components also require this component

*/

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

	// the constructor sets the position, rotation and scale of the entity
	TransformComponent(Vector2D p, float a, float s)
	{
		position = p;
		angle = a;
		scale = s;
	}

	// This method returns the position of the entity
	Vector2D getPosition();

	// This method sets the position of the entity
	void setPosition(Vector2D newPosition);

	// This method adds a position to current position of the entity
	void addPosition(Vector2D newPosition);

	// This method returns the rotation of the entity
	float getRotation();

	// This method sets the rotation of the entity
	void setRotation(float newAngle);

	// This method adds a rotation to current rotation of the entity
	void addRotation(float newAngle);

	// This method returns the scale of the entity
	float getScale();

	// This method sets the scale of the entity
	void setScale(float newScale);

	// This method adds a scale to current scale of the entity
	void addScale(float newScale);

};