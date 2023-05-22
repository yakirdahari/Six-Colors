#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Graph.h"
#include "Hexagon.h"
#include "Player.h"

class Window
{
public:
    Window(const float& width, const float& height);

    void run(std::shared_ptr<Graph<Shape>> graph, std::shared_ptr<Player> player);
    
    bool isOpen();

private:
    std::shared_ptr <sf::RenderWindow> m_window;
    std::vector<std::shared_ptr<sf::RectangleShape>> m_colorButtons;
    std::vector<std::shared_ptr<Shape>> m_shapes;
    Colors m_colors{};

    void initButtons();
    void initInfo();
    void processEvents(std::shared_ptr<Player> player,
                       std::shared_ptr<Graph<Shape>> graph);
    void handleMouseClick(int x, int y, std::shared_ptr<Player> player,
                          std::shared_ptr<Graph<Shape>> graph);
    void update(std::shared_ptr<Player> player);
    void render(std::shared_ptr<Graph<Shape>> graph);

    // Info
    sf::Font m_font;
    sf::Text m_playerControl;
    sf::Text m_computerControl;

};
