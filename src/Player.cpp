#include "Player.h"

Player::Player() : control(0)
{
}

void Player::pickColor(sf::Color color, std::shared_ptr<Graph<Shape>> graph)
{
	if (m_paintedEdges.empty())
	{
		m_paintedEdges.push_back(graph->getRoot());
	}
	for (auto& edge : m_paintedEdges)
	{
		edge->setColor(color);
	}
	//graph->getEdges()[0]->setColor(color);
	graph->resetVisited();

	// use DFS to get all neighbours with identical color
	m_paintedEdges = graph->playerDFS(graph->getRoot(), color);
	
	// update control
	setControl((float)m_paintedEdges.size() / (float)graph->getEdges().size());
	std::cout << "player: " << areaControlled() << std::endl;
}

void Player::setControl(float amount)
{
	control = amount;
}

float Player::areaControlled()
{
	return control;
}
