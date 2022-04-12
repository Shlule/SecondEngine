#pragma once
#include"MoveComponent.h"
#include<SDL_stdinc.h>
class InputComponent : MoveComponent
{
public:
	InputComponent(Actor* ownerP);
	InputComponent() = delete;
	InputComponent(const InputComponent&) =delete;
	InputComponent& operator=(const InputComponent&) = delete;

	void processInput(const Uint8* keyState);

	void setMaxForwardSpeed(float maxForwardSpeedP);
	void setMaxAngularSpeed(const float maxAngularSpeedP);
	void setForwardKey(int key);
	void setBackwardKey(int key);
	void setClockwiseKey(int key);
	void setCounterClockwiseKey(int key);

private:
	float maxForwardSpeed;
	float maxAngularSpeed;

	int forwardKey;
	int backwardKey;
	int clockwiseKey;
	int counterClockwiseKey;
};

