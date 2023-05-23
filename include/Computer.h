#pragma once

#include "Graph.h"
#include "Shape.h"
#include "Easy.h"
#include "Medium.h"

class Computer
{
public:
	/*--------------------------------*\
   |----------- CONSTRUCTOR ------------|
	\*--------------------------------*/

	Computer(const int& difficulty);

	/*--------------------------------*\
   |------------ FUNCTIONS -------------|
	\*--------------------------------*/

	void pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph);
	void setControl(const float& amount);
	void setStartingPoint(const std::shared_ptr<Shape>& edge);
	void setChosenColor(const sf::Color& color);
	std::unordered_set<std::shared_ptr<Shape>> paintedEdges();
	float areaControlled() const;		// how much area player controls
	sf::Color chosenColor() const;

private:
	std::shared_ptr<ComputerState> m_state;
};