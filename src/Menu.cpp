#include "Menu.h"


Menu::Menu()
	: m_windowWidth(404), m_windowHeight(480),
	m_window(sf::VideoMode(404, 480), "6 Colors", sf::Style::Titlebar | sf::Style::Close)
{
	initTitle();
	initButtons();
}


Menu::~Menu()
{
}


void Menu::run()
{
	while (m_window.isOpen())
	{
		draw();
		updateEvents();
	}
}


void Menu::draw()
{
	m_window.clear(sf::Color(130, 130, 130));

	// Draw the screen
	m_window.draw(title);
	m_window.draw(easy);
	m_window.draw(hard);
	m_window.draw(expert);

	m_window.display();
}


void Menu::updateEvents()
{
	sf::Vector2f mousePos;
	mousePos.x = (float)(sf::Mouse::getPosition(m_window).x);
	mousePos.y = (float)(sf::Mouse::getPosition(m_window).y);
	for (auto event = sf::Event(); m_window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}


		if (easy.getGlobalBounds().contains(mousePos))
		{
			easy.setCharacterSize(47);
			easy.setOutlineThickness(5);
			easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 180 - 7);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.close();
				auto g = Game(1);
				g.run();
			}
		}
		else
		{
			easy.setCharacterSize(40);
			easy.setOutlineThickness(3);
			easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 180);
		}

		if (hard.getGlobalBounds().contains(mousePos))
		{
			hard.setCharacterSize(47);
			hard.setOutlineThickness(5);
			hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 270 - 7);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.close();
				auto g = Game(2);
				g.run();
			}
		}
		else
		{
			hard.setCharacterSize(40);
			hard.setOutlineThickness(3);
			hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 270);
		}

		if (expert.getGlobalBounds().contains(mousePos))
		{
			expert.setCharacterSize(47);
			expert.setOutlineThickness(5);
			expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 360 - 7);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.close();
				auto g = Game(3);
				g.run();
			}
		}
		else
		{
			expert.setCharacterSize(40);
			expert.setOutlineThickness(3);
			expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 360);
		}
	}
}


void Menu::initTitle()
{
	titleFont.loadFromFile("Title_Font.TTF");
	title.setString("6 COLORS");
	title.setFont(titleFont);
	title.setCharacterSize(80);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(7);
	title.setPosition(((m_windowWidth / 2.f) - (title.getGlobalBounds().width / 2.f)), 40);
}


void Menu::initButtons()
{
	buttonsFont.loadFromFile("Buttons_Font.ttf");

	// easy
	easy.setString("EASY");
	easy.setFont(buttonsFont);
	easy.setFillColor(sf::Color::Yellow);
	easy.setOutlineColor(sf::Color::Black);
	easy.setOutlineThickness(3);
	easy.setCharacterSize(40);
	easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 180);

	// hard
	hard.setString("HARD");
	hard.setFont(buttonsFont);
	hard.setFillColor(sf::Color(255, 150, 22));
	hard.setOutlineColor(sf::Color::Black);
	hard.setOutlineThickness(3);
	hard.setCharacterSize(40);
	hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 270);

	// expert
	expert.setString("EXPERT");
	expert.setFont(buttonsFont);
	expert.setFillColor(sf::Color(170, 0, 170));
	expert.setOutlineColor(sf::Color::Black);
	expert.setOutlineThickness(3);
	expert.setCharacterSize(40);
	expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 360);
}



