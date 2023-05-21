#pragma once

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <memory>
#include "Player.h"
#include "Window.h"

class Game
{
public:
	/*--------------------------------*\
   |----------- CONSTRUCTOR ------------|
	\*--------------------------------*/

	Game();

	/*--------------------------------*\
   |------------ FUNCTIONS -------------|
	\*--------------------------------*/

	void run();

	/*--------------------------------*\
   |--------------- ENUM ---------------|
	\*--------------------------------*/

	enum GraphSize
	{
		graphWidth = 29,
		graphHeight = 35,
	};

	enum WindowSize
	{
		windowWidth = 402,
		windowHeight = 550,
	};

	/*--------------------------------*\
   |------------ DESTRUCTOR ------------|
	\*--------------------------------*/

	~Game();

private:
	// Our world
	std::shared_ptr<Window> m_window;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Graph<Shape>> m_graph;

	void generateBoard();	// create a graph by width and height
	void link(std::vector<std::vector<std::shared_ptr<Shape>>> hexagons);
	// belong to window
	// void handleEvents();
	// void updateInfo();         // refreshes counters
	// void initInfo();	// Creates the information line
	// sf::Font infoFont;
	// sf::Text level;
	// sf::Text playerScore;
	// sf::Text computerScore;

};