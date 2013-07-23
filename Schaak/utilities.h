#pragma once
#include <SFML/Graphics/Rect.hpp>

template <typename T>
inline sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
    return sf::Vector2<T>(left.x * right.x, left.y * right.y);
};
