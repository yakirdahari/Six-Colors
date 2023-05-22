#pragma once

#include "Shape.h"

// Constructor
Shape::Shape(const int& vertices) : m_sp(7.2, vertices), m_vertices(vertices)
{   
	//m_sp.setOrigin(sf::Vector2f(150.f, 150.f));
	//m_sp.setFillColor(color);
	m_sp.setOutlineColor(sf::Color::Black);
    m_sp.setOutlineThickness(0.5);
	m_sp.scale(1.0f, 0.9f);
}

void Shape::setColor(const sf::Color& color)
{
	m_sp.setFillColor(color);
}

void Shape::setPosition(const sf::Vector2f& position)
{
	m_sp.setPosition(position);
}

sf::Color Shape::getColor()
{
    return m_sp.getFillColor();
}

void Shape::draw(sf::RenderWindow& window) const
{
	window.draw(m_sp);
}

void Shape::randomColor()
{
    // pick a random color
    int random = rand() % m_colors().size();

    // set the shape's color
    m_sp.setFillColor(m_colors[random]);
}

const int& Shape::vertices()
{
    return m_vertices;
}

float Shape::getWidth() const
{
    return m_sp.getRadius() * 2.0f;
}

float Shape::getHeight() const
{
    return m_sp.getRadius() * 2.0f;
}