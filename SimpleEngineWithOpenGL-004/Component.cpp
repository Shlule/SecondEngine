#include "Component.h"
#include"Actor.h"

Component::Component(Actor* ownerP, int UpdateOrderP):owner(*ownerP) ,updateOrder (UpdateOrderP)
{
	// le component appelle la fonction addcomponent de l'actor pour s'ajouter;
	owner.addComponent(this);
}
Component::~Component() {
	owner.removeComponent(this);
}

void Component::update(float dt) {

}
void Component::processInput(const Uint8* keyState){
}