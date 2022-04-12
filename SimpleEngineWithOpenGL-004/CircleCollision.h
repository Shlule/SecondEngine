#pragma once
#include"Component.h"
#include"Vector2.h"
class CircleCollision : public Component
{
public:
	CircleCollision(Actor* owner);
	CircleCollision() = delete;
	CircleCollision(const CircleCollision&) = delete;
	CircleCollision& operator=(const CircleCollision) = delete;

	float getRadius()const;
	void setRadius(float radiusP);

	const Vector2 getCenter()const;

private:
	float radius;

};
bool Intersect(const CircleCollision& a, const CircleCollision& b);

