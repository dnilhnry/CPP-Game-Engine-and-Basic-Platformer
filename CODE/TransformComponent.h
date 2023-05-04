#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	Vector2D position;
	float angle;
	float scale;
	bool physicsEnabled;
	PhysicsComponent* pPC;
	double frameTime;

public:

	TransformComponent(Vector2D p, float a, float s)
	{
		position = p;
		angle = a;
		scale = s;
		physicsEnabled = false;
	}

	TransformComponent(Vector2D p, float a, float s, bool physics)
	{
		position = p;
		angle = a;
		scale = s;
		physicsEnabled = physics;
	}

	void setPhysicsComponent(PhysicsComponent* pc)
	{
		pPC = pc;
	}

	void update() override
	{
		if (physicsEnabled == false)
		{
			// do nothing
		}
		if (physicsEnabled == true)
		{
			position = pPC->getNewPosition(position);
		}
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

	bool getPhysics()
	{
		return physicsEnabled;
	}

	void setPhysics(bool physics)
	{
		physicsEnabled = physics;
	}

};