#include "Menu.h"
#include "Game.h"


Menu::Menu()
	: m_windowWidth(1440), m_windowHeight(900),
	m_window(sf::VideoMode(700, 720), "6 Colors", sf::Style::Titlebar | sf::Style::Close)
{
	initTitle();
	initButtons();
}


Menu::~Menu()
{
	//auto hard = hard();
	//hard.run(m_window);
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
	m_window.clear(sf::Color::Black);

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
				m_window.clear(sf::Color::Cyan);
				m_window.display();

			}
		}


		if (easy.getGlobalBounds().contains(mousePos))
		{
			easy.setCharacterSize(90);
			easy.setOutlineThickness(4);
			easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 400 - 15);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.clear(sf::Color::Black);
				auto g = Game(1);
				g.run();
			}
		}
		else
		{
			easy.setCharacterSize(70);
			easy.setOutlineThickness(0);
			easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 400);
		}

		if (hard.getGlobalBounds().contains(mousePos))
		{
			hard.setCharacterSize(90);
			hard.setOutlineThickness(4);
			hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 550 - 15);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//m_window.close();
				//auto h = hard();
				//h.run();
				Menu::~Menu();
			}
		}
		else
		{
			hard.setCharacterSize(70);
			hard.setOutlineThickness(0);
			hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 550);
		}

		if (expert.getGlobalBounds().contains(mousePos))
		{
			expert.setCharacterSize(90);
			expert.setOutlineThickness(4);
			expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 700 - 15);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.close();
			}
		}
		else
		{
			expert.setCharacterSize(70);
			expert.setOutlineThickness(0);
			expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 700);
		}
	}
}


void Menu::initTitle()
{
	//titleFont.loadFromFile("font7.TTF");
	titleFont.loadFromFile("Title_Font.TTF");
	title.setString("6 COLORS");
	title.setFont(titleFont);
	title.setCharacterSize(280);
	title.setFillColor(sf::Color(0, 183, 183));
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(5);
	title.setPosition(((m_windowWidth / 2.f) - (title.getGlobalBounds().width / 2.f)), 30);
}


void Menu::initButtons()
{
	buttonsFont.loadFromFile("Buttons_Font.ttf");

	// easy
	easy.setString("EASY");
	easy.setFont(buttonsFont);
	easy.setFillColor(sf::Color(244, 189, 0));
	easy.setOutlineColor(sf::Color::White);
	easy.setCharacterSize(70);
	easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 400);

	// hard
	hard.setString("HARD");
	hard.setFont(buttonsFont);
	hard.setFillColor(sf::Color(255, 66, 128));
	hard.setOutlineColor(sf::Color::White);
	hard.setCharacterSize(70);
	hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 550);

	// expert
	expert.setString("EXPERT");
	expert.setFont(buttonsFont);
	expert.setFillColor(sf::Color(170, 0, 170));
	expert.setOutlineColor(sf::Color::White);
	expert.setCharacterSize(70);
	expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 700);
}



