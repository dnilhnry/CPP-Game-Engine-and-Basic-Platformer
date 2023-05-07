/*

The InputComponent is used to check for inputs from the user
the player entity should contain an InputComponent
if the users uses the input keys, this component will call methods from the PhysicsComponent

*/

#pragma once

#include "Components.h"
#include "myinputs.h"

class InputComponent : public Component
{
private:
	MyInputs* pInputs;
	PhysicsComponent* pPC;

	bool firstInput;

public:
	// constructor - sets the pointer to the input tool
	InputComponent(MyInputs* i)
	{
		pInputs = i;
		firstInput = false;
	}

	// sets the required variables
	void init() override
	{
		pPC = &entity->getComponent<PhysicsComponent>();
	}

	// checks if the user has pressed enter key
	bool getFirstInput();

	// checks for inputs from the user
	// if the first input is pressed,
	// inputs call methods from the player's PhysicsComponent
	void checkForInputs();

};