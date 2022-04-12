#include "Actor.h"
#include<algorithm>
#include"Game.h"
#include"Component.h"
#include"Math.h"

Actor::Actor() :
	state(Actor::ActorState::Active),
	position(Vector2::zero),
	scale(1.0f),
	rotation(0.0f),
	game(Game::instance())
{
	game.addActor(this);
}

Actor::~Actor() {
	game.removeActor(this);
	// need to delete components
	//because~component calls RemoveComponent , need a difgferent style loop
	while (!components.empty()) {
		delete components.back();
	}
}

void Actor::setPosition(Vector2 positionP) {
	position = positionP;
}
void Actor::setRotation(float rotationP) {
	rotation = rotationP;
}
void Actor::setScale(float scaleP) {
	scale = scaleP;
}
void Actor::update(float dt) {
	if (state == Actor::ActorState::Active) {
		updateComponent(dt);
		updateActor(dt);
	}
}
void Actor::updateComponent(float dt) {
	for (auto component : components) {
		component->update(dt);
	}
}
void Actor::updateActor(float dt)
{
}
void Actor::addComponent(Component* component) {
	//find the insertion point in the stored vector
	//(the fist element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto iter = begin(components);
	for (; iter != end(components); iter++) {
		if (myOrder < (*iter)->getUpdateOrder()) {
			break;
		}
	}
	//inserts element before position of iterator
	components.insert(iter, component);
}
//la fonxtion vas chercher l'index du components correspond , le stocker dans un iterateur, et les supprimer garce a cette index.
void Actor::removeComponent(Component* component) {
	auto iter = std::find(begin(components), end(components), component);
	if (iter != end(components)) {
		components.erase(iter);
	}
}
Vector2 Actor::getForward()const {
	return Vector2(Maths::cos(rotation), -Maths::sin(rotation));
}
void Actor::processInput(const Uint8* keyState) {
	if (state == Actor::ActorState::Active) {
		for (auto component : components) {
			component->processInput(keyState);
		}
		actorInput(keyState);
	}
}
void Actor::actorInput(const Uint8* keyState) {
}