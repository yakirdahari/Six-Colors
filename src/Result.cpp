#include "Result.h"

Result::Result(float score)
	: m_windowWidth(404), m_windowHeight(480), m_score(score),
	m_window(sf::VideoMode(404, 480), "6 Colors", sf::Style::Titlebar | sf::Style::Close)
{
	initTitleWin();
	initTitleLoss();
	initNewButton();
	initScore();
}

Result::~Result()
{
}

void Result::run()
{
	while (m_window.isOpen())
	{
		draw();
		updateEvents();
	}
}

void Result::draw()
{
	m_window.clear(sf::Color(130, 130, 130));

	if (m_score >= 0.5f)
	{
		m_window.draw(titleWin);
		m_window.draw(score);
	}
	else
	{
		m_window.draw(titleLoss);
	}
	m_window.draw(newButton);

	m_window.display();
}

void Result::updateEvents()
{
	sf::Vector2f mousePos;
	mousePos.x = (float)(sf::Mouse::getPosition(m_window).x);
	mousePos.y = (float)(sf::Mouse::getPosition(m_window).y);
	for (auto event = sf::Event(); m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			exit(EXIT_SUCCESS);
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}

		if (newButton.getGlobalBounds().contains(mousePos))
		{
			newButton.setCharacterSize(45);
			newButton.setOutlineThickness(5);
			newButton.setPosition(((m_windowWidth / 2.f) - (newButton.getGlobalBounds().width / 2.f)), 360 - 7);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.close();
				auto m = Menu();
				m.run();
			}
		}
		else
		{
			newButton.setCharacterSize(40);
			newButton.setOutlineThickness(3);
			newButton.setPosition(((m_windowWidth / 2.f) - (newButton.getGlobalBounds().width / 2.f)), 360);
		}
	}
}

void Result::initTitleWin()
{
	titleFont.loadFromFile("Title_Font.TTF");
	titleWin.setString("YOU HAVE WON!");
	titleWin.setFont(titleFont);
	titleWin.setCharacterSize(53);
	titleWin.setFillColor(sf::Color::White);
	titleWin.setOutlineColor(sf::Color::Black);
	titleWin.setOutlineThickness(7);
	titleWin.setPosition(((m_windowWidth / 2.f) - (titleWin.getGlobalBounds().width / 2.f)), 60);
}

void Result::initTitleLoss()
{
	titleFont.loadFromFile("Title_Font.TTF");
	titleLoss.setString("YOU LOST!");
	titleLoss.setFont(titleFont);
	titleLoss.setCharacterSize(80);
	titleLoss.setFillColor(sf::Color::White);
	titleLoss.setOutlineColor(sf::Color::Black);
	titleLoss.setOutlineThickness(7);
	titleLoss.setPosition(((m_windowWidth / 2.f) - (titleLoss.getGlobalBounds().width / 2.f)), 40);
}

void Result::initNewButton()
{
	buttonsFont.loadFromFile("Buttons_Font.ttf");
	newButton.setString("NEW GAME");
	newButton.setFont(buttonsFont);
	newButton.setFillColor(sf::Color(170, 0, 170));
	newButton.setOutlineColor(sf::Color::Black);
	newButton.setOutlineThickness(3);
	newButton.setCharacterSize(40);
	newButton.setPosition(((m_windowWidth / 2.f) - (newButton.getGlobalBounds().width / 2.f)), 360);
}

void Result::initScore()
{
	score.setString("YOUR SCORE IS: " + std::to_string(m_score));
	score.setFont(buttonsFont);
	score.setCharacterSize(25);
	score.setFillColor(sf::Color(255, 150, 22));
	score.setOutlineColor(sf::Color::Black);
	score.setOutlineThickness(3);
	score.setPosition(((m_windowWidth / 2.f) - (score.getGlobalBounds().width / 2.f)), 220);
}
