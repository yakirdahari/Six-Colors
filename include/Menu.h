
#include <SFML/Graphics.hpp>
#include "Game.h"



class Menu
{
public:

	// Constractor
	Menu();							// Constractor
	~Menu();						// Destractor

	// Public Functions
	void run();						// running the program.

private:
	// Members
	sf::RenderWindow m_window;
	int m_windowHeight;
	int m_windowWidth;

	// Fonts
	sf::Font titleFont;
	sf::Font buttonsFont;

	// Texts
	sf::Text title;
	sf::Text easy;
	sf::Text hard;
	sf::Text expert;

	// Private Functions
	void draw();					// Draws the objects on the screen.
	void updateEvents();			// Handles screen events.
	void initTitle();				// Creates the title.
	void initButtons();				// Creates the buttons.
};