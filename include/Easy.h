#pragma once

#include "ComputerState.h"

class Easy : public ComputerState
{
public:
	virtual void pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph) override;
	void pickRandomColor(sf::Color playerColor);
};