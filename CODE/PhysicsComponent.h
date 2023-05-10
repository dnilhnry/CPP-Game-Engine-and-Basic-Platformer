/*

The PhysicsComponent is used to apply velocity and acceleration to an entity
it is used by the player entity to move and jump and constantly apply gravity

*/

#pragma once

#include "Components.h"
#include "Vector2D.h"

class PhysicsComponent : public Component
{
private:
	TransformComponent* pTC;

	Vector2D position;
	Vector2D velocity;
	float velocityX;
	float velocityY;
	Vector2D acceleration;
	float accelerationX;
	float accelerationY;

	float movementSpeed;
	float jumpSpeed;
	float gravity;
	bool jumpReady;

	double frameTime;

public:
	// constructor - takes movement speed, jump speed and gravity
	PhysicsComponent(float ms, float js, float g)
	{
		movementSpeed = ms;
		jumpSpeed = js;
		gravity = g;
	}

	// initialise the components required variables
	void init() override
	{
		pTC = &entity->getComponent<TransformComponent>();
		position = pTC->getPosition();
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(0, 0);
		jumpReady = false;
	}

	// update the position based on the velocity and acceleration and frame time
	void update() override
	{
		if (isActive() == true)
		{
			frameTime = entity->getGameTime();
			position = pTC->getPosition();
			setVelocity();
			setAcceleration();
			if (!(acceleration.YValue + gravity) == 0)
			{
				jumpReady = false;
			}
			velocity = velocity + (acceleration + Vector2D(0, gravity)) * frameTime;
			position = position + velocity * frameTime;
			if (position.XValue <= -353)
			{
				position = position + Vector2D(704, 0);
			}
			if (position.XValue >= 353)
			{
				position = position + Vector2D(-704, 0);
			}
			setVelocityX(0.0f);
			setVelocityY(velocity.YValue);
			setAccelerationX(0.0f);

			// reduce accelerationY by real life time not every frame
			if (accelerationY > 1)
			{
				setAccelerationY(accelerationY / 10);
			}
			else if (accelerationY <= 1)
			{
				setAccelerationY(0.0f);
			}

			pTC->setPosition(position);
		}
	}

	// set the velocity vector based on the velocityX and velocityY
	void setVelocity();

	// returns the velocity vector
	Vector2D getVelocity();

	// sets the velocity x value
	void setVelocityX(float x);

	// sets the velocity y value
	void setVelocityY(float y);

	// sets the acceleration vector based on the accelerationX and accelerationY
	void setAcceleration();

	// gets the acceleration vector
	Vector2D getAcceleration();

	// sets the acceleration x value
	void setAccelerationX(float x);

	// sets the acceleration y value
	void setAccelerationY(float y);

	// returns the movement speed
	float getMovementSpeed();

	// sets the movement speed
	void setMovementSpeed(float s);

	// returns the jump speed
	float getJumpSpeed();

	// sets the jump speed
	void setJumpSpeed(float s);

	// returns the gravity
	float getGravity();

	// sets the gravity
	void setGravity(float g);

	// adds acceleration if jumpReady is true 
	void jump();

	// sets velocityX to -movementSpeed
	void moveLeft();

	// sets velocityX to movementSpeed
	void moveRight();

	// sets jumpReady to true
	// stops the player from falling through the ground
	void stableGround();

	// stops the player from moving through a platform
	void bounceBack();

};