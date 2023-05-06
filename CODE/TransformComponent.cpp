#include "Components.h"

Vector2D TransformComponent::getPosition()
{
	return position;
}

void TransformComponent::setPosition(Vector2D newPosition)
{
	position = newPosition;
}

void TransformComponent::addPosition(Vector2D newPosition)
{
	position = position + newPosition;
}

float TransformComponent::getRotation()
{
	return angle;
}

void TransformComponent::setRotation(float newAngle)
{
	angle = newAngle;
}

void TransformComponent::addRotation(float newAngle)
{
	angle = angle + newAngle;
}

float TransformComponent::getScale()
{
	return scale;
}

void TransformComponent::setScale(float newScale)
{
	scale = newScale;
}

void TransformComponent::addScale(float newScale)
{
	scale = scale + newScale;
}