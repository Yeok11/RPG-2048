#pragma once
#include <functional>
#include "pch.h"
#include "TimeManager.h"
#include "Core.h"

template <typename T>
T Lerp(const T& start, const T& end, float t)
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

bool IsEnd(Vec2 start, Vec2 end) {
    return start == end;
}

void DOLerp(Vec2& start, const Vec2& end) {

    float elapsedTime = 0.0f;

    while (elapsedTime < 1.0f) {
        float t = elapsedTime / 1.0f;
        t = std::clamp(t, 0.0f, 1.0f);
        start = Lerp(start, end, t);

        GET_SINGLE(Core)->CoreRender();
        GET_SINGLE(Core)->CoreUpdate();

        elapsedTime += fDT;
    }

    start = end;
}
