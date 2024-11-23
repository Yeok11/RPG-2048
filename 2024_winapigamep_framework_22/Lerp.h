#pragma once
#include <algorithm>
#include "Vec2.h"

template <typename T>
T Lerp(const T& strat, const T& end, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);
	return start + (end - start) * t;
}

Vec2 Lerp(const Vec2& start, const Vec2& end, float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return Vec2(
        start.x + (end.x - start.x) * t,
        start.y + (end.y - start.y) * t
    );
}

