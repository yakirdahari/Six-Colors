#pragma once

#include "ComputerState.h"

class Medium : public ComputerState
{
public:
	virtual void pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph) override;
	void checkAvailableColors(const sf::Color playerColor);
private:
	std::vector<std::shared_ptr<sf::Color>> m_availableColors;
};