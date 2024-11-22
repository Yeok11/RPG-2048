#pragma once
#include <algorithm>

template <typename T>
T Lerp(const T& strat, const T& end, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);
	return start + (end - start) * t;
}
