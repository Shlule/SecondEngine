#include "CircleCollision.h"
#include"Actor.h"

CircleCollision::CircleCollision(Actor* owner): Component(owner), radius(1.0f)
{}
float CircleCollision::getRadius()const {
	return owner.getScale() * radius;
}
void CircleCollision::setRadius(float radiusP) {
	radius = radiusP;
}
const Vector2 CircleCollision::getCenter()const {
	return owner.getPosition();
}
bool Intersect(const CircleCollision& a, const CircleCollision& b) {
	Vector2 aCenter = a.getCenter();
	Vector2 bCenter = b.getCenter();
	Vector2 ab = bCenter - aCenter;

	float distSQ = ab.lenghtSq();
	float sumOfRadius = a.getRadius() + b.getRadius();
	return distSQ <= sumOfRadius * sumOfRadius;
}
