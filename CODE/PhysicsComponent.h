#pragma once

#include "Components.h"
#include "Vector2D.h"

class PhysicsComponent : public Component
{
private:
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
	PhysicsComponent(float ms, float js, float g)
	{
		movementSpeed = ms;
		jumpSpeed = js;
		gravity = g;
	}

	void init() override
	{
		TransformComponent* pTC = &entity->getComponent<TransformComponent>();
		pTC->setPhysicsComponent(this);
		InputComponent* pIC = &entity->getComponent<InputComponent>();
		pIC->setPhysicsComponent(this);
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(0, 0);
		jumpReady = false;
	}

	void update(double ft) override
	{
		frameTime = ft;
	}

	Vector2D getNewPosition(Vector2D currentPosition)
	{
		position = currentPosition;

		setVelocity();
		setAcceleration();
		if (!(acceleration.YValue + gravity) == 0)
		{
			jumpReady = false;
		}
		velocity = velocity + (acceleration + Vector2D(0, gravity));
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
		setAccelerationX(0.0f);
		if (accelerationY > 1)
		{
			setAccelerationY(accelerationY / 10);
		}
		else if (accelerationY <= 1)
		{
			setAccelerationY(0.0f);
		}

		return position;
	}

	void setVelocity()
	{
		velocity = Vector2D(velocityX, velocityY);
	}

	Vector2D getVelocity()
	{
		setVelocity();
		return velocity;
	}

	void setVelocityX(float x)
	{
		velocityX = x;
	}

	void setVelocityY(float y)
	{
		velocityY = y;
	}

	void setAcceleration()
	{
		acceleration = Vector2D(accelerationX, accelerationY);
	}

	Vector2D getAcceleration()
	{
		setAcceleration();
		return acceleration;
	}

	void setAccelerationX(float x)
	{
		accelerationX = x;
	}

	void setAccelerationY(float y)
	{
		accelerationY = y;
	}

	float getMovementSpeed()
	{
		return movementSpeed;
	}

	void setMovementSpeed(float s)
	{
		movementSpeed = s;
	}

	float getJumpSpeed()
	{
		return jumpSpeed;
	}

	void setJumpSpeed(float s)
	{
		jumpSpeed = s;
	}

	float getGravity()
	{
		return gravity;
	}

	void setGravity(float g)
	{
		gravity = g;
	}

	void jump()
	{
		// could be better
		// https://gamedev.stackexchange.com/questions/121389/how-i-can-make-better-jump-to-my-game-c-sfml

		if (jumpReady == true)
		{
			jumpReady = false;
			setAccelerationY(jumpSpeed);
		}
	}

	void moveLeft()
	{
		setVelocityX(-movementSpeed);
	}

	void moveRight()
	{
		setVelocityX(movementSpeed);
	}

	void stableGround()
	{
		jumpReady = true;
		accelerationY = accelerationY - gravity;
	}

};