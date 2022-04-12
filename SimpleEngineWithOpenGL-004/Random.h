#pragma once
#include<random>
#include"Vector2.h"
class Random
{
public:
	static void init();

	//seed generator with the specified int
	//NOTE: you should generally not need to manually use this
	static void seed(unsigned int seed);

	// Get a float from between 0.0 and 1.0
	static float getFloat();

	//get a float from the specified range
	static float getFloatRange(float min, float max);

	//get an int from the specified range
	static int getIntRange(int min, int max);

	// get a random vector given -the/ min/max bounds
	static Vector2 getVector2(const Vector2& min, const Vector2& max);

private:
	static std::mt19937 sGenerator;
};

