#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Graph.h"
#include "Hexagon.h"
#include "Player.h"

class Window
{
public:
    Window(float width, float height);

    void run(std::shared_ptr<Graph<Shape>> graph, std::shared_ptr<Player> player);
    bool isOpen();

private:
    sf::RenderWindow m_window;
    std::vector<sf::Color> m_colors;
    std::vector<sf::RectangleShape> m_colorButtons;
    std::vector<std::shared_ptr<Shape>> m_shapes;

    void processEvents(std::shared_ptr<Player> player,
                       std::shared_ptr<Graph<Shape>> graph);
    void handleMouseClick(int x, int y, std::shared_ptr<Player> player,
                          std::shared_ptr<Graph<Shape>> graph);
    void render(std::shared_ptr<Graph<Shape>> graph);
};
