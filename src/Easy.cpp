#include "Easy.h"

void Easy::pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph)
{
	// get stuff ready for DFS
	pickRandomColor(playerColor);
	//graph->resetVisited();

	// paint owned edges
	for (auto& edge : m_paintedEdges)
	{
		edge->setColor(chosenColor());
	}

	// use DFS to get all neighbours with identical color
	m_paintedEdges = graph->DFS(m_startingPoint, chosenColor());

	// update control
	float newControl = static_cast<float>(m_paintedEdges.size()) / static_cast<float>(graph->getEdges().size());
	setControl(newControl);
}

void Easy::pickRandomColor(sf::Color playerColor)
{
	int random = rand() % m_colors().size();

	// color can't match the player's and computer's color
	while (m_colors[random] == chosenColor() ||
		   m_colors[random] == playerColor)
	{
		random = rand() % m_colors().size();
	}
	setChosenColor(m_colors[random]);
}
