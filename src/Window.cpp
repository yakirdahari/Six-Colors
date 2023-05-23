#include "Window.h"
#include "Menu.h"

Window::Window(const float& width, const float& height) :
    m_window(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height),
                        "6 Colors", sf::Style::Titlebar | sf::Style::Close)),
    waitingForPlayer(true)
{
    initTextures();
    initButtons();
    initInfo();
    initNewButton();
}

void Window::run(std::shared_ptr<Graph<Shape>> graph, std::shared_ptr<Player> player,
                 std::shared_ptr<Computer> computer)
{
    waitingForPlayer = true;

    // we don't put those in the loop to improve performance
    update(player, computer);
    render(graph);

    // wait for player to choose a color
    while (m_window->isOpen() && waitingForPlayer)
    {
        processEvents(player, graph, computer);
    }
}

void Window::initButtons()
{
    // button size
    float buttonWidth = 25.f;
    float buttonHeight = 25.f;

    for (size_t i = 0; i < m_colors().size(); ++i) {
        auto button = std::make_shared<sf::RectangleShape>(sf::Vector2f(buttonWidth, buttonHeight));
        button->setPosition((m_window->getSize().x / 3.8) + i * buttonWidth * 1.3, m_window->getSize().y - buttonHeight * 3.4);
        button->setFillColor(m_colors[i]);

        m_colorButtons.push_back(button);
    }
}

void Window::initTextures()
{
    if (!m_disabledButtonTexture1.loadFromFile("X.png"))
    {
        throw std::exception("failed to load X.png");
    }
    m_disabledButton1.setTexture(m_disabledButtonTexture1);
    m_disabledButton1.scale(0.6f, 0.6f);
    m_disabledButton1.setOrigin(m_disabledButton1.getLocalBounds().width * (-0.17f), m_disabledButton1.getLocalBounds().height * (-0.17f));

    if (!m_disabledButtonTexture2.loadFromFile("X.png"))
    {
        throw std::exception("failed to load X.png");
    }
    m_disabledButton2.setTexture(m_disabledButtonTexture2);
    m_disabledButton2.scale(0.6f, 0.6f);
    m_disabledButton2.setOrigin(m_disabledButton2.getLocalBounds().width * (-0.17f), m_disabledButton2.getLocalBounds().height * (-0.17f));
}

void Window::clearButtons()
{
    m_disabledButton1.setPosition(1000, 1000);
    m_disabledButton2.setPosition(1000, 1000);
}

void Window::initInfo()
{
    if (!m_font.loadFromFile("Buttons_Font.ttf"))
    {
        throw std::exception("failed to load font");
    }

    // text configuration
    int textSize = 18;

    // player
    m_playerControl.setString("");
    m_playerControl.setFillColor(sf::Color::White);
    m_playerControl.setCharacterSize(textSize);
    m_playerControl.setPosition((m_window->getSize().x * 0.06), m_window->getSize().y * 0.925);
    m_playerControl.setFont(m_font);

    // computer
    m_computerControl.setString("");
    m_computerControl.setFillColor(sf::Color::White);
    m_computerControl.setCharacterSize(textSize);
    m_computerControl.setPosition((m_window->getSize().x * 0.7), m_window->getSize().y * 0.925);
    m_computerControl.setFont(m_font);
}

void Window::initNewButton()
{
    m_new.setString("NEW");
    m_new.setFont(m_font);
    m_new.setCharacterSize(34);
    m_new.setFillColor(sf::Color::White);
    m_new.setOutlineColor(sf::Color::Black);
    //m_new.setOutlineThickness(4);
    m_new.setPosition((m_window->getSize().x / 2.f) - (m_new.getGlobalBounds().width / 2.f), m_window->getSize().y * 0.9);
}

bool Window::isOpen()
{
    return m_window->isOpen() ? true : false;
}

void Window::processEvents(std::shared_ptr<Player> player,
                           std::shared_ptr<Graph<Shape>> graph,
                           std::shared_ptr<Computer> computer)
{
    sf::Event event;

    sf::Vector2f mousePos;

    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window->close();
        else if (event.type == sf::Event::MouseButtonPressed &&
                 event.mouseButton.button == sf::Mouse::Left)
        {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;
            handleMouseClick(x, y, player, graph, computer);
        }
    }
}

void Window::handleMouseClick(int x, int y, std::shared_ptr<Player> player,
                              std::shared_ptr<Graph<Shape>> graph,
                              std::shared_ptr<Computer> computer)
{
    for (const auto& button : m_colorButtons) {
        if (button->getGlobalBounds().contains(x, y) &&
            button->getFillColor() != player->chosenColor() &&
            button->getFillColor() != computer->chosenColor()) {
            player->pickColor(button->getFillColor(), graph);
            waitingForPlayer = false;
            break;
        }
    }
    if (m_new.getGlobalBounds().contains(x, y))
    {
        m_window->close();
        auto m = Menu();
        m.run();
    }
}

void Window::update(std::shared_ptr<Player> player, std::shared_ptr<Computer> computer)
{
    m_playerControl.setString(std::to_string(player->areaControlled()));
    m_computerControl.setString(std::to_string(computer->areaControlled()));

    // delete existing X from disabled buttons
    clearButtons();

    // add X to 1st disabled button
    for (const auto& button : m_colorButtons)
    {
        if (button->getFillColor() == player->chosenColor())
        {
            m_disabledButton1.setPosition(button->getPosition());
        }
        if (button->getFillColor() == computer->chosenColor())
        {
            m_disabledButton2.setPosition(button->getPosition());
        }
    }
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
    m_window->draw(m_computerControl);
    m_window->draw(m_disabledButton1);
    m_window->draw(m_disabledButton2);
    m_window->draw(m_new);

    m_window->display();
}
