#pragma once

#include "Graph.h"
#include "Shape.h"

class ComputerState
{
public:
	/*--------------------------------*\
   |------------ FUNCTIONS -------------|
	\*--------------------------------*/

	virtual void pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph) = 0;
	virtual void setControl(const float& amount);
	virtual void setStartingPoint(const std::shared_ptr<Shape>& edge);
	virtual void setChosenColor(const sf::Color& color);
	virtual float areaControlled() const;		// how much area player controls
	virtual sf::Color chosenColor() const;
	virtual std::unordered_set<std::shared_ptr<Shape>> paintedEdges() const;

	/*--------------------------------*\
   |------------ DESTRUCTOR ------------|
	\*--------------------------------*/

	virtual ~ComputerState() = default;

protected:
	std::unordered_set<std::shared_ptr<Shape>> m_paintedEdges;
	sf::Color m_currentColor;
	std::shared_ptr<Shape> m_startingPoint;
	Colors m_colors;
	float m_control;
};