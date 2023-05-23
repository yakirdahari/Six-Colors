#pragma once

#include "ComputerState.h"

class Expert : public ComputerState
{
public:
	virtual void pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph) override;
	int checkGain(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph);
	void checkAvailableColors(const sf::Color playerColor);
private:
	std::vector<std::shared_ptr<sf::Color>> m_availableColors;
	std::unordered_set<std::shared_ptr<Shape>> highestSize;
	sf::Color bestChoice;
	sf::Color maxColor;
};