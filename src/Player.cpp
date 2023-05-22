#include "Player.h"

Player::Player() : m_control(0)
{
}

void Player::pickColor(const sf::Color color, std::shared_ptr<Graph<Shape>> graph)
{
	// get stuff ready for DFS
	m_startingPoint->setColor(color);
	graph->resetVisited();
	
	// paint owned edges
	for (auto& edge : m_paintedEdges)
	{
		edge->setColor(color);
	}

	// use DFS to get all neighbours with identical color
	m_paintedEdges = graph->DFS(m_startingPoint, color);

	// update control
	float newControl = static_cast<float>(m_paintedEdges.size()) / static_cast<float>(graph->getEdges().size());
	setControl(newControl);
}

void Player::setControl(const float& amount)
{
	m_control = amount;
}

void Player::setStartingPoint(const std::shared_ptr<Shape>& edge)
{
	m_startingPoint = edge;
}

void Player::setChosenColor(const sf::Color& color)
{
	m_currentColor = color;
}

float Player::areaControlled()
{
	return m_control;
}

sf::Color Player::chosenColor()
{
	return m_currentColor;
}
