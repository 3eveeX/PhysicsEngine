#pragma once
#include <raylib.h>

inline float GetRandomFloat() {
	return (float)GetRandomValue(0, 10000) / 10000.0f;
}