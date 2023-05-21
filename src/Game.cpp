#include "Game.h"

Game::Game() : m_player(std::make_shared<Player>()),
               m_graph(std::make_shared<Graph<Shape>>()),
               m_window(std::make_shared<Window>(windowWidth, windowHeight))
{
    generateBoard();
}

void Game::run()
{
    while (m_player->areaControlled() < 0.50)
    {
        m_window->run(m_graph, m_player);
    }
}

Game::~Game()
{
}

void Game::generateBoard()
{
    // create hexagons and store their shared pointers in a 2D vector
    std::vector<std::vector<std::shared_ptr<Shape>>> hexagons(graphHeight, std::vector<std::shared_ptr<Shape>>(graphWidth));
    int offset;

    // create hexagons and add them to the graph
    for (int i = 0; i < graphHeight; i++)
    {
        for (int j = 0; j < graphWidth -1; j++)
        {
            auto hexagon = std::make_shared<Hexagon>(); // Create a shared_ptr to Hexagon

            // every 2nd row is dented to the side
            i % 2 == 0 ? offset = 0 : offset = hexagon->getWidth() * -0.6;
            hexagon->setPosition(sf::Vector2f(hexagon->getWidth() * j + offset, 0.75 * hexagon->getHeight() * i ));
            hexagons[i][j] = hexagon;
            m_graph->addEdge(hexagon); // Add the hexagon to the graph
        }
        if (i % 2 == 1)
        {
            // every 2nd row has an extra hexagon
            auto hexagon = std::make_shared<Hexagon>(); // Create a shared_ptr to Hexagon
            offset = hexagon->getWidth() * -0.6;
            hexagon = std::make_shared<Hexagon>(); // Create a shared_ptr to Hexagon
            hexagon->setPosition(sf::Vector2f(hexagon->getWidth() * (graphWidth -1) + offset, 0.75 * hexagon->getHeight() * i));
            hexagons[i][graphWidth -1] = hexagon;
            m_graph->addEdge(hexagon); // Add the hexagon to the graph
        }
    }
    // link each hexagon with its neighbours
    link(hexagons);

    // randomize the colors of the hexagons
    m_graph->randomizeColors();
}

void Game::link(std::vector<std::vector<std::shared_ptr<Shape>>> hexagons)
{
    for (int i = 0; i < graphHeight; i++)
    {
        for (int j = 0; j < graphWidth -1; j++)
        {
            auto hexagon = hexagons[i][j];

            // connect left & right
            if (j > 0)
            {
                auto leftNeighbor = hexagons[i][j - 1];
                m_graph->addNeighbour(hexagon, leftNeighbor);
            }

            // connect top-left & bottom-right
            if ((i > 0 && i % 2 == 0) ||
                (i > 0 && j > 0 && i % 2 == 1))
            {
                auto topLeftNeighbor = hexagons[i - 1][j];
                m_graph->addNeighbour(hexagon, topLeftNeighbor);
            }

            // connect top-right & bottom-left 
            if ((i > 0 && j < graphWidth - 2) ||
                (i > 0 && j < graphWidth - 1 && i % 2 == 0))
            {
                auto topRightNeighbor = hexagons[i - 1][j + 1];
                m_graph->addNeighbour(hexagon, topRightNeighbor);
            }
        }
    }
}

