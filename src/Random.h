#include "raylib.h"
#include "raymath.h"
class Random {

public:

	inline static float GetRandomFloat(float max = 10000) {
		return GetRandomValue(0, max) / (float)max;
	}
	
	inline static float GetRandomFloat(float min, float max = 10000) {
		return min + GetRandomFloat() * (max - min);
	}

};