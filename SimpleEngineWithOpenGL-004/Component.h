#pragma once
#include<SDL_stdinc.h>

class Actor;

class Component
{
public:
	Component(Actor* ownerP, int UpdateOrderP = 100);
	Component();
	virtual~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void update(float dt);

	virtual void processInput(const Uint8* keyState);

	virtual void onUpdateWorldTransform() {}

protected:
	Actor& owner;
	int updateOrder;
};

