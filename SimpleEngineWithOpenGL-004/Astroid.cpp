#include "Astroid.h"
#include"Random.h"
#include"Window.h"
#include"Math.h"
#include"SpriteComponent.h"
#include"moveComponent.h"
#include"Assets.h"

Astroid::Astroid() :Actor()
{
	Vector2 randPos = Random::getVector2(Vector2::zero, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
	setPosition(randPos);
	setRotation(Random::getFloatRange(0.0f, Maths::twoPi));

	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Astroid"));
	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(150.0f);
}