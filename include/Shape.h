#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include "Colors.h"

class Shape
{
public:
	/*--------------------------------*\
   |----------- CONSTRUCTOR ------------|
    \*--------------------------------*/

	Shape(const int& vertices);

	/*--------------------------------*\
   |------------ FUNCTIONS -------------|
	\*--------------------------------*/

	virtual void setColor(const sf::Color& color);
	virtual void setPosition(const sf::Vector2f& position);
	virtual sf::Color getColor();
	virtual void draw(sf::RenderWindow& window) const;
	virtual void randomColor();
	virtual const int& vertices();
	virtual float getWidth() const;
	virtual float getHeight() const;

	
	void thick();
	void thin();

	/*--------------------------------*\
   |------------ DESTRUCTOR ------------|
    \*--------------------------------*/

	virtual ~Shape() = default;

protected:
	sf::CircleShape m_sp;
	const int& m_vertices;
	Colors m_colors{};
};