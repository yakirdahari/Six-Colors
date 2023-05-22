#include "ComputerState.h"

void ComputerState::setControl(const float& amount)
{
	m_control = amount;
}

void ComputerState::setStartingPoint(const std::shared_ptr<Shape>& edge)
{
	m_startingPoint = edge;
}

void ComputerState::setChosenColor(const sf::Color& color)
{
	m_startingPoint->setColor(color);
	m_currentColor = color;
}

float ComputerState::areaControlled() const
{
	return m_control;
}

sf::Color ComputerState::chosenColor() const
{
	return m_currentColor;
}

std::unordered_set<std::shared_ptr<Shape>> ComputerState::paintedEdges() const
{
	return m_paintedEdges;
}
