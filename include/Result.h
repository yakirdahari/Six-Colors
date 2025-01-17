#pragma once

#include "Menu.h"
#include "Game.h"

class Result
{
public:
	// constractor & destractor
	Result(float score);
	~Result();

	//public functions
	void run();


private:
	//members
	sf::RenderWindow m_window;
	int m_windowHeight;
	int m_windowWidth;
	float m_score;

	//fonts
	sf::Font titleFont;
	sf::Font buttonsFont;

	//texst
	sf::Text titleWin;
	sf::Text titleLoss;
	sf::Text newButton;
	sf::Text score;

	//private functions
	void draw();					// Draws the objects on the screen.
	void updateEvents();			// Handles screen events.
	void initTitleWin();
	void initTitleLoss();
	void initNewButton();
	void initScore();
};