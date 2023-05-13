#include "Components.h"

void PhysicsComponent::setVelocity()
{
	velocity = Vector2D(velocityX, velocityY);
}

Vector2D PhysicsComponent::getVelocity()
{
	return velocity;
}

void PhysicsComponent::setVelocityX(float x)
{
	velocityX = x;
}

void PhysicsComponent::setVelocityY(float y)
{
	velocityY = y;
}

void PhysicsComponent::setAcceleration()
{
	acceleration = Vector2D(accelerationX, accelerationY);
}

Vector2D PhysicsComponent::getAcceleration()
{
	return acceleration;
}

void PhysicsComponent::setAccelerationX(float x)
{
	accelerationX = x;
}

void PhysicsComponent::setAccelerationY(float y)
{
	accelerationY = y;
}

float PhysicsComponent::getMovementSpeed()
{
	return movementSpeed;
}

void PhysicsComponent::setMovementSpeed(float s)
{
	movementSpeed = s;
}

float PhysicsComponent::getJumpSpeed()
{
	return jumpSpeed;
}

void PhysicsComponent::setJumpSpeed(float s)
{
	jumpSpeed = s;
}

float PhysicsComponent::getGravity()
{
	return gravity;
}

void PhysicsComponent::setGravity(float g)
{
	gravity = g;
}

void PhysicsComponent::jump()
{
	if (jumpReady == true)
	{
		jumpReady = false;
		impulseTime = 0.01f;
		setAccelerationY(jumpSpeed);
	}
}

void PhysicsComponent::moveLeft()
{
	setVelocityX(-movementSpeed);
}

void PhysicsComponent::moveRight()
{
	setVelocityX(movementSpeed);
}

void PhysicsComponent::stableGround()
{
	jumpReady = true;
	accelerationY =  -gravity;
	velocityY = 1.0f;
}

void PhysicsComponent::bounceBack()
{
	accelerationY = gravity;
	velocityY = -10.0f;
}