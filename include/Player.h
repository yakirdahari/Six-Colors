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
	void setControl(float amount);
	void setStartingPoint(std::shared_ptr<Shape> edge);
	float areaControlled();		// how much area player controls

private:
	std::unordered_set<std::shared_ptr<Shape>> m_paintedEdges;
	sf::Color currentColor;
	std::shared_ptr<Shape> startingPoint;
	float control;
};
