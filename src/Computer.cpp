#include "Computer.h"

Computer::Computer(const int& difficulty)
{
	switch (difficulty)
	{
	case 1:
		m_state = std::make_shared<Easy>();
		break;
	case 2:
		m_state = std::make_shared<Medium>();
	}
}

void Computer::pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph)
{
	m_state->pickColor(playerColor, graph);
}

void Computer::setControl(const float& amount)
{
	m_state->setControl(amount);
}

void Computer::setStartingPoint(const std::shared_ptr<Shape>& edge)
{
	m_state->setStartingPoint(edge);
}

void Computer::setChosenColor(const sf::Color& color)
{
	m_state->setChosenColor(color);
}

std::unordered_set<std::shared_ptr<Shape>> Computer::paintedEdges()
{
	return m_state->paintedEdges();
}

float Computer::areaControlled() const
{
	return m_state->areaControlled();
}

sf::Color Computer::chosenColor() const
{
	return m_state->chosenColor();
}

