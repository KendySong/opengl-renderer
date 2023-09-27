#include "Math.hpp"

float Math::lerp(float a, float b, float t)
{
    return (1 - t) * a + t * b;
}