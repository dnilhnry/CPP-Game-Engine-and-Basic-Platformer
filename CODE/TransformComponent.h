#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
private:
	Vector2D position;
	float angle;
	float scale;

	bool physics;

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

	TransformComponent(Vector2D p, float a, float s, bool phys, float ms, float js, float g)
	{
		position = p;
		angle = a;
		scale = s;
		physics = phys;
		movementSpeed = ms;
		jumpSpeed = js;
		gravity = g;
	}

	void init() override
	{
		position = Vector2D(0, 0);
		angle = 0;
		scale = 1;

		physics = false;
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(0, 0);
		movementSpeed = 0;
		jumpSpeed = 0;
		gravity = 0;
		jumpReady = false;
		frameTime = false;
	}

	void update() override
	{
		if (physics == false)
		{

		}
		if (physics == true)
		{
			setVelocity();
			setAcceleration();
			if (!(acceleration.YValue + gravity) == 0)
			{
				jumpReady = false;
			}
			velocity = velocity + (acceleration + Vector2D(0, gravity)) * frameTime;
			position = position + velocity * frameTime;
			setVelocityX(0);
			// setVelocityY(0);
			setAccelerationX(0);
			setAccelerationY(0);
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

	float getRotation()
	{
		return angle;
	}

	void setRotation(float newAngle)
	{
		angle = newAngle;
	}

	float getScale()
	{
		return scale;
	}

	void setScale(float newScale)
	{
		scale = newScale;
	}

	bool getPhysics()
	{
		return physics;
	}

	void setPhysics(bool p)
	{
		physics = p;
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
		velocityX = y;
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
		accelerationX = y;
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
		setAccelerationY(-gravity);
		setVelocityY(0);
	}

	double getFrameTime()
	{
		return frameTime;
	}

	void setFrameTime(double t)
	{
		frameTime = t;
	}

};