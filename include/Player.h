#pragma once

#include <memory>
#include "Graph.h"
#include "Shape.h"

class Player
{
public:
	/*--------------------------------*\
   |----------- CONSTRUCTOR ------------|
    \*--------------------------------*/

	Player();
	
	/*--------------------------------*\
   |------------ FUNCTIONS -------------|
	\*--------------------------------*/

	void pickColor(const sf::Color color, std::shared_ptr<Graph<Shape>> graph);
	void setControl(const float& amount);
	void setStartingPoint(const std::shared_ptr<Shape>& edge);
	void setChosenColor(const sf::Color& color);
	std::unordered_set<std::shared_ptr<Shape>> paintedEdges();
	float areaControlled();		// how much area player controls
	sf::Color chosenColor();

private:
	std::unordered_set<std::shared_ptr<Shape>> m_paintedEdges;
	sf::Color m_currentColor;
	std::shared_ptr<Shape> m_startingPoint;
	float m_control;
};
