#include "Player.h"

Player::Player() : m_control(0.f)
{
}

void Player::pickColor(const sf::Color color, std::shared_ptr<Graph<Shape>> graph)
{
	// get stuff ready for DFS
	setChosenColor(color);
	m_startingPoint->setColor(color);
	auto visited = graph->getVisited();
	//std::unordered_set<std::shared_ptr<Shape>> neighbours;

	// paint owned edges
	for (auto& edge : m_paintedEdges)
	{
		edge->setColor(color);
	}

	// use DFS to get all neighbours with identical color
	graph->DFS(m_startingPoint, color, m_paintedEdges, visited);

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
	m_paintedEdges.insert(edge);
}

void Player::setChosenColor(const sf::Color& color)
{
	m_currentColor = color;
}

std::unordered_set<std::shared_ptr<Shape>> Player::paintedEdges()
{
	return m_paintedEdges;
}

float Player::areaControlled()
{
	return m_control;
}

sf::Color Player::chosenColor()
{
	return m_currentColor;
}

