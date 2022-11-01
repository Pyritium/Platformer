#pragma once

#include <iostream>
#include <cmath>
#include <map>

#ifndef PI
#define PI 3.1415926545
#endif

typedef double(*EasingFunction)(double);

template <typename T>
constexpr T clamp(const T& n, const T& lo, const T& hi)
{
	return std::max(lo, std::min(n, hi));
}

bool CompareDouble(double a, double b)
{
	return fabs(a - b) < DBL_EPSILON;
}

float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
    return lv.x * rv.x + lv.y * rv.y;
}

sf::Vector2f normalise(sf::Vector2f source)
{
    float length = std::sqrt(dot(source, source));
    if (length != 0) source /= length;
    return source;
}

sf::Vector3f getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal)
{
    //the collision normal is stored in x and y, with the penetration in z
    sf::Vector3f manifold;
    //std::cout << overlap.width << " | " << overlap.height << std::endl;
    if ((overlap.width) < overlap.height)
    {
        manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
        manifold.z = overlap.width;
    }
    else
    {
        manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
        manifold.z = overlap.height;
    }

    return manifold;
}


