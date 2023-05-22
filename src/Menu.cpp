#include "Menu.h"
#include "Game.h"


Menu::Menu()
	: m_windowWidth(730), m_windowHeight(700),
	m_window(sf::VideoMode(730, 700), "6 Colors", sf::Style::Titlebar | sf::Style::Close)
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
			easy.setCharacterSize(65);
			easy.setOutlineThickness(6);
			easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 270 - 10);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.close();
				auto g = Game(1);
				g.run();
			}
		}
		else
		{
			easy.setCharacterSize(55);
			easy.setOutlineThickness(3);
			easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 270);
		}

		if (hard.getGlobalBounds().contains(mousePos))
		{
			hard.setCharacterSize(65);
			hard.setOutlineThickness(6);
			hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 400 - 10);
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
			hard.setCharacterSize(55);
			hard.setOutlineThickness(3);
			hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 400);
		}

		if (expert.getGlobalBounds().contains(mousePos))
		{
			expert.setCharacterSize(65);
			expert.setOutlineThickness(6);
			expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 530 - 10);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.close();
			}
		}
		else
		{
			expert.setCharacterSize(55);
			expert.setOutlineThickness(3);
			expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 530);
		}
	}
}


void Menu::initTitle()
{
	titleFont.loadFromFile("Title_Font.TTF");
	title.setString("6 COLORS");
	title.setFont(titleFont);
	title.setCharacterSize(150);
	//title.setFillColor(sf::Color(0, 183, 183));
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
	//easy.setFillColor(sf::Color(244, 189, 0));
	easy.setOutlineColor(sf::Color::Black);
	easy.setOutlineThickness(3);
	easy.setCharacterSize(55);
	easy.setPosition(((m_windowWidth / 2.f) - (easy.getGlobalBounds().width / 2.f)), 270);

	// hard
	hard.setString("HARD");
	hard.setFont(buttonsFont);
	hard.setFillColor(sf::Color(255, 150, 22));
	//hard.setFillColor(sf::Color(255, 66, 128));
	hard.setOutlineColor(sf::Color::Black);
	hard.setOutlineThickness(3);
	hard.setCharacterSize(55);
	hard.setPosition(((m_windowWidth / 2.f) - (hard.getGlobalBounds().width / 2.f)), 400);

	// expert
	expert.setString("EXPERT");
	expert.setFont(buttonsFont);
	expert.setFillColor(sf::Color(170, 0, 170));
	expert.setOutlineColor(sf::Color::Black);
	expert.setOutlineThickness(3);
	expert.setCharacterSize(55);
	expert.setPosition(((m_windowWidth / 2.f) - (expert.getGlobalBounds().width / 2.f)), 530);
}



