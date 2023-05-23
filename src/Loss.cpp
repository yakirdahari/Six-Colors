#include "Loss.h"

Loss::Loss(float score)
	: m_windowWidth(404), m_windowHeight(480), m_score(score),
	m_window(sf::VideoMode(404, 480), "6 Colors", sf::Style::Titlebar | sf::Style::Close)
{
	initTitleWin();
	initTitleLoss();
	initNewButton();
	initScore();
}

Loss::~Loss()
{
}

void Loss::run()
{
	while (m_window.isOpen())
	{
		draw();
		updateEvents();
	}
}

void Loss::draw()
{
	m_window.clear(sf::Color(130, 130, 130));

	if (m_score >= 0.05f)
	{
		m_window.draw(titleWin);
	}
	else
	{
		m_window.draw(titleLoss);
	}
	m_window.draw(newButton);
	m_window.draw(score);

	m_window.display();
}

void Loss::updateEvents()
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
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}
	}
}

void Loss::initTitleWin()
{
	titleFont.loadFromFile("Title_Font.TTF");
	titleWin.setString("YOU HAVE WON!");
	titleWin.setFont(titleFont);
	titleWin.setCharacterSize(50);
	titleWin.setFillColor(sf::Color::White);
	titleWin.setOutlineColor(sf::Color::Black);
	titleWin.setOutlineThickness(7);
	titleWin.setPosition(((m_windowWidth / 2.f) - (titleWin.getGlobalBounds().width / 2.f)), 40);
}

void Loss::initTitleLoss()
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

void Loss::initNewButton()
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

void Loss::initScore()
{
	score.setString("");
	score.setFont(buttonsFont);
	score.setCharacterSize(40);
	score.setFillColor(sf::Color::White);
	score.setOutlineColor(sf::Color::Black);
	score.setOutlineThickness(7);
	score.setPosition(((m_windowWidth / 2.f) - (score.getGlobalBounds().width / 2.f)), 40);
}
