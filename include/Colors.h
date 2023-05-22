#pragma once

#include <memory>
#include <SFML/Graphics/Color.hpp>
#include <vector>

// umm I think the colors go here :p
class Colors
{
public:
	/*--------------------------------*\
   |----------- CONSTRUCTOR ------------|
    \*--------------------------------*/

    Colors() : m_colors({ std::make_shared<sf::Color>(sf::Color::Red) ,
               std::make_shared<sf::Color>(255, 165, 0), // Orange
               std::make_shared<sf::Color>(sf::Color::Yellow),
               std::make_shared<sf::Color>(sf::Color::Green),
               std::make_shared<sf::Color>(sf::Color::Blue),
               std::make_shared<sf::Color>(sf::Color::Magenta) }) {};

    /*--------------------------------*\
   |------------ OPERATORS -------------|
    \*--------------------------------*/

    // operator ()
    std::vector<std::shared_ptr<sf::Color>> operator()()
    {
        return m_colors;
    }

    // operator []
    sf::Color operator[](size_t index)
    {
        return *m_colors[index];
    }

    const sf::Color& operator[](size_t index) const
    {
        return *m_colors[index];
    }
    
private:
    std::vector<std::shared_ptr<sf::Color>> m_colors;
};