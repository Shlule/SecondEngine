#pragma once
#include<Vector>
#include"Vector2.h"
#include"Matrix4.h"
#include<SDL_stdinc.h>
using std::vector;

class Game;
class Component;

class Actor
{
public:
	enum class ActorState {
		Active,
		Paused,
		Dead
	};
	Actor();
	virtual~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	const Matrix4& getWorldTransform() const { return worldTransform; }
	void computeWorldTransform();

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector2 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const float getRotation() const { return rotation; }

	void setPosition(Vector2 positionP);
	void setScale(float scaleP);
	void setRotation(float rotation);

	void update(float dt);
	void updateComponent(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* componentP);
	void removeComponent(Component* componentP);

	Vector2 getForward()const;

	void processInput(const Uint8* keyState);
	virtual void actorInput(const Uint8* keyState);

private:
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform;
	Game& game;
	ActorState state;
	Vector2 position;
	float rotation;
	float scale;

	vector<Component*> components;
};

