#include "Player.h"

Player::Player() : control(0)
{
}

void Player::pickColor(const sf::Color color, std::shared_ptr<Graph<Shape>> graph)
{
	// get stuff ready for DFS
	startingPoint->setColor(color);
	graph->resetVisited();
	
	// paint owned edges
	for (auto& edge : m_paintedEdges)
	{
		edge->setColor(color);
	}

	// use DFS to get all neighbours with identical color
	m_paintedEdges = graph->DFS(startingPoint, color);

	// update control
	float newControl = static_cast<float>(m_paintedEdges.size()) / static_cast<float>(graph->getEdges().size());
	setControl(newControl);
}

void Player::setControl(float amount)
{
	control = amount;
}

void Player::setStartingPoint(std::shared_ptr<Shape> edge)
{
	startingPoint = edge;
}

float Player::areaControlled()
{
	return control;
}
