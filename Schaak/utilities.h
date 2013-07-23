#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <stdlib.h>

template <typename T>
inline sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
    return sf::Vector2<T>(left.x * right.x, left.y * right.y);
};

template <typename T>
inline sf::Vector2<T> operator /(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
    return sf::Vector2<T>(left.x / right.x, left.y / right.y);
};

template <typename T>
inline T bound(T x, T minimum, T maximum)
{
	return std::max(std::min(x,maximum),minimum);
}

// iterate over a rectangular area
class MapIterator
{
public:
	//MapIterator()
	//{
	//	initialise(sf::IntRect(0,0,MAP_WIDTH,MAP_HEIGHT));
	//}
	MapIterator(sf::Vector2i range)
	{
		initialise(sf::IntRect(sf::Vector2i(0,0),range));
	}
	MapIterator(sf::IntRect range)
	{
		initialise(range);
	}
	MapIterator(int x, int y, int xr, int yr)
	{
		initialise(sf::IntRect(x,y,xr,yr));
	}
	inline void zero() {current.x=r.left; current.y=r.top;}
	inline sf::Vector2i operator*() const {return current;}
	inline void operator++()
	{
		current.x++;
		if(current.x >= max.x)
		{
			current.x = r.left;
			current.y++;
			if(current.y>=max.y)
				inRange = false;
		}
	}
	inline bool good(){return inRange;}
private:
	inline void initialise(sf::IntRect range)
	{
		r = range;
		max.x = r.left+r.width;
		max.y = r.top+r.height;
		zero();
		inRange = true;

	}
	bool inRange;
	sf::Vector2i current;
	sf::Vector2i max;
	sf::IntRect r;
};
