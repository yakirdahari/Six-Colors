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

	void pickColor(sf::Color color, std::shared_ptr<Graph<Shape>> graph);
	void setControl(float amount);
	float areaControlled();		// how much area player controls

private:
	std::vector<std::shared_ptr<Shape>> m_paintedEdges;
	sf::Color currentColor;
	float control;
};
