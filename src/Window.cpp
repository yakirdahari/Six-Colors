#include "Window.h"

Window::Window(const float& width, const float& height) :
    m_window(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height),
                         "6 Colors", sf::Style::Titlebar | sf::Style::Close))
{
    initButtons();
    initInfo();
}

void Window::run(std::shared_ptr<Graph<Shape>> graph, std::shared_ptr<Player> player)
{
    processEvents(player, graph);
    update(player);
    render(graph);
}

void Window::initButtons()
{
    // button size
    float buttonWidth = 25.f;
    float buttonHeight = 25.f;

    for (size_t i = 0; i < m_colors().size(); ++i) {
        auto button = std::make_shared<sf::RectangleShape>(sf::Vector2f(buttonWidth, buttonHeight));
        button->setPosition((m_window->getSize().x / 3.8) + i * buttonWidth * 1.3, m_window->getSize().y - buttonHeight * 1.4);
        button->setFillColor(m_colors[i]);

        m_colorButtons.push_back(button);
    }
}

void Window::initInfo()
{
    m_font.loadFromFile("Buttons_Font.otf");

    // text configuration
    int textSize = 16;

    m_playerControl.setString("");
    m_playerControl.setFillColor(sf::Color::White);
    m_playerControl.setCharacterSize(textSize);
    m_playerControl.setPosition((m_window->getSize().x * 0.04), m_window->getSize().y * 0.925);
    m_playerControl.setFont(m_font);
}

bool Window::isOpen()
{
    return m_window->isOpen() ? true : false;
}

void Window::processEvents(std::shared_ptr<Player> player,
                           std::shared_ptr<Graph<Shape>> graph)
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window->close();
        else if (event.type == sf::Event::MouseButtonPressed &&
                 event.mouseButton.button == sf::Mouse::Left)
        {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            handleMouseClick(x, y, player, graph);
        }
    }
}

void Window::handleMouseClick(int x, int y, std::shared_ptr<Player> player,
                              std::shared_ptr<Graph<Shape>> graph)
{
    for (const auto& button : m_colorButtons) {
        if (button->getGlobalBounds().contains(x, y)) {
            player->pickColor(button->getFillColor(), graph); // Call pickColor on the player with the selected color
            break;
        }
    }
}

void Window::update(std::shared_ptr<Player> player)
{
    m_playerControl.setString(std::to_string(player->areaControlled()));
}

void Window::render(std::shared_ptr<Graph<Shape>> graph)
{
    m_window->clear(sf::Color(130, 130, 130));
    std::vector<std::shared_ptr<Shape>> hexagons = graph->getEdges();

    // draw hexagons
    for (const auto& hexagon : hexagons) {
        hexagon->draw(*m_window);
    }

    // draw color buttons
    for (const auto& button : m_colorButtons) {
        m_window->draw(*button);
    }

    // draw info
    m_window->draw(m_playerControl);

    m_window->display();
}
