#include "Window.h"

Window::Window(int width, int height) :
    m_window(sf::VideoMode(width, height), "6 Colors", sf::Style::Titlebar | sf::Style::Close),
    m_colors({sf::Color::Red,
              sf::Color(255, 165, 0), // Orange
              sf::Color::Yellow,
              sf::Color::Green,
              sf::Color::Blue,
              sf::Color::Magenta})
{
    // Create hexagons and assign colors
    for (const auto& color : m_colors) {
        std::shared_ptr<Hexagon> hexagon = std::make_shared<Hexagon>();
        hexagon->setColor(color);
        m_shapes.push_back(hexagon);
    }

    // Set up the color buttons
    float buttonWidth = 25.f;
    float buttonHeight = 25.f; // Adjust as needed

    for (size_t i = 0; i < m_colors.size(); ++i) {
        sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
        button.setPosition((width/3) + i * buttonWidth * 1.2, height - buttonHeight);
        button.setFillColor(m_colors[i]);

        m_colorButtons.push_back(button);
    }
}

void Window::run(std::shared_ptr<Graph<Shape>> graph, std::shared_ptr<Player> player)
{
    while (m_window.isOpen())
    {
        processEvents(player, graph);
        update();
        render(graph);
    }
}

void Window::processEvents(std::shared_ptr<Player> player,
                           std::shared_ptr<Graph<Shape>> graph)
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
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
        if (button.getGlobalBounds().contains(x, y)) {
            player->pickColor(button.getFillColor(), graph); // Call pickColor on the player with the selected color
            break;
        }
    }
}

void Window::update()
{
    // Update any necessary logic here
}

void Window::render(std::shared_ptr<Graph<Shape>> graph)
{
    m_window.clear(sf::Color(130, 130, 130));
    std::vector<std::shared_ptr<Shape>> m_hexagons = graph->getEdges();

    // Draw hexagons
    for (const auto& hexagon : m_hexagons) {
        hexagon->draw(m_window);
    }

    // Draw color buttons
    for (const auto& button : m_colorButtons) {
        m_window.draw(button);
    }

    m_window.display();
}
