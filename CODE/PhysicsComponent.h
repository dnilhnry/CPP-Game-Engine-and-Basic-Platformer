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
	PhysicsComponent(float ms, float js, float g)
	{
		movementSpeed = ms;
		jumpSpeed = js;
		gravity = g;
	}

	void init() override
	{
		pTC = &entity->getComponent<TransformComponent>();
		position = pTC->getPosition();
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(0, 0);
		jumpReady = false;
	}

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

	void setVelocity();

	Vector2D getVelocity();

	void setVelocityX(float x);

	void setVelocityY(float y);

	void setAcceleration();

	Vector2D getAcceleration();

	void setAccelerationX(float x);

	void setAccelerationY(float y);

	float getMovementSpeed();

	void setMovementSpeed(float s);

	float getJumpSpeed();

	void setJumpSpeed(float s);

	float getGravity();

	void setGravity(float g);

	void jump();

	void moveLeft();

	void moveRight();

	void stableGround();

};