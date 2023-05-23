#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Graph.h"
#include "Hexagon.h"
#include "Player.h"
#include "Computer.h"

class Window
{
public:
    Window(const float& width, const float& height);

    void run(std::shared_ptr<Graph<Shape>> graph, std::shared_ptr<Player> player,
             std::shared_ptr<Computer> computer);
    
    bool isOpen();
    void render(std::shared_ptr<Graph<Shape>> graph);

private:
    std::shared_ptr <sf::RenderWindow> m_window;
    std::vector<std::shared_ptr<sf::RectangleShape>> m_colorButtons;
    std::vector<std::shared_ptr<Shape>> m_shapes;
    Colors m_colors{};
    bool waitingForPlayer;
    sf::Text m_new;

    void initButtons();
    void initTextures();
    void initNewButton();
    void clearButtons();
    void initInfo();
    void processEvents(std::shared_ptr<Player> player,
                       std::shared_ptr<Graph<Shape>> graph,
                       std::shared_ptr<Computer> computer);
    void handleMouseClick(int x, int y, std::shared_ptr<Player> player,
                          std::shared_ptr<Graph<Shape>> graph,
                          std::shared_ptr<Computer> computer);
    void update(std::shared_ptr<Player> player, std::shared_ptr<Computer> computer);

    // info
    sf::Font m_font;
    sf::Text m_playerControl;
    sf::Text m_computerControl;

    // X image for disabled buttons
    sf::Sprite m_disabledButton1;
    sf::Texture m_disabledButtonTexture1;

    sf::Sprite m_disabledButton2;
    sf::Texture m_disabledButtonTexture2;   
};
