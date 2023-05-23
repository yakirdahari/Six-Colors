#include "Game.h"
#include "Result.h"

Game::Game(const int& difficulty) : m_player(std::make_shared<Player>()),
                                    m_computer(std::make_shared<Computer>(difficulty)), 
                                    m_graph(std::make_shared<Graph<Shape>>()),
                                    m_window(std::make_shared<Window>(windowWidth, windowHeight))
{
}

void Game::run()
{
    generateBoard();

    try
    {
        std::unordered_set<std::shared_ptr<Shape>> edges;
        while (m_window->isOpen() &&
            (m_player->areaControlled() < 0.50 && m_computer->areaControlled() < 0.50))
        {
            // player's turn
            edges = m_player->paintedEdges();
            //White(edges);
            m_window->run(m_graph, m_player, m_computer);
            //edges = m_player->paintedEdges();
            //White(edges);
            //Black(edges);

            if (m_player->areaControlled() > 0.5)
            {
                m_window->~Window();
                auto e = Result(m_player->areaControlled());
                e.run();
            }
            
            
            // player's turn  
            playerTurn();
            computerTurn();

            // computer's turn
            edges = m_computer->paintedEdges();
            //White(edges);
            m_computer->pickColor(m_player->chosenColor(), m_graph);
            edges = m_computer->paintedEdges();
            //White(edges);
            //Black(edges);

            if (m_computer->areaControlled() > 0.5)
            {
                m_window->~Window();
                auto e = Result(m_player->areaControlled());
                e.run();
            }
        }
    }
    catch (std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
}

Game::~Game()
{
    
}

void Game::generateBoard()
{
    // 2d vector helps link the hexagons
    std::vector<std::vector<std::shared_ptr<Shape>>> hexagons(graphHeight, std::vector<std::shared_ptr<Shape>>(graphWidth));
    float offset;

    // create hexagons and add them to the graph
    for (int i = 0; i < graphHeight; i++)
    {
        for (int j = 0; j < graphWidth -1; j++)
        {
            // create a new hexagon
            auto hexagon = std::make_shared<Hexagon>();

            // every 2nd row is dented to the side
            i % 2 == 0 ? offset = 0 : offset = hexagon->getWidth() * -0.6;
            hexagon->setPosition(sf::Vector2f(hexagon->getWidth() * j + offset, 0.75 * hexagon->getHeight() * i ));
            hexagons[i][j] = hexagon;
            m_graph->addEdge(hexagon); // add the hexagon to the graph
        }
        if (i % 2 == 1)
        {
            // every 2nd row has an extra hexagon
            auto hexagon = std::make_shared<Hexagon>();
            offset = hexagon->getWidth() * -0.6;
            hexagon->setPosition(sf::Vector2f(hexagon->getWidth() * (graphWidth -1) + offset, 0.75 * hexagon->getHeight() * i));
            hexagons[i][graphWidth -1] = hexagon;
            m_graph->addEdge(hexagon); // add the hexagon to the graph
        }
    }
    // set graph's root
    m_graph->setRoot(hexagons[graphHeight - 1][0]);

    // link each hexagon with its neighbours
    link(hexagons);

    // randomize colors till the color of player and computer don't match
    while (hexagons[graphHeight - 1][0]->getColor() == hexagons[0][graphWidth - 2]->getColor())
    {
        m_graph->randomizeColors();
    }

    // starting points for player and computer
    m_player->setStartingPoint(hexagons[graphHeight - 1][0]);
    m_player->setChosenColor(hexagons[graphHeight - 1][0]->getColor());
    m_computer->setStartingPoint(hexagons[0][graphWidth - 2]);
    m_computer->setChosenColor(hexagons[0][graphWidth - 2]->getColor());

    // initialise control of area
    float startingControl = 1.f / m_graph->getEdges().size();
    m_player->setControl(startingControl);
    m_computer->setControl(startingControl);
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
                auto leftNeighbour = hexagons[i][j - 1];
                m_graph->addNeighbour(hexagon, leftNeighbour);
            }

            // connect top-left & bottom-right
            if (i > 0 && i % 2 == 0)           // even rows
            {
                auto topLeftNeighbour = hexagons[i - 1][j];
                    m_graph->addNeighbour(hexagon, topLeftNeighbour);
            }
            if (i > 0 && j > 0 && i % 2 == 1)  // odd rows
            {
                auto topLeftNeighbour = hexagons[i - 1][j - 1];
                m_graph->addNeighbour(hexagon, topLeftNeighbour);
            }

            // connect top-right & bottom-left
            if (i > 0 && j < graphWidth - 1 && i % 2 == 0)  // even rows
            {
                auto topRightNeighbour = hexagons[i - 1][j + 1];
                m_graph->addNeighbour(hexagon, topRightNeighbour);
            }
            if (i > 0 && j < graphWidth - 2)                // odd rows
            {
                auto topRightNeighbour = hexagons[i - 1][j];
                m_graph->addNeighbour(hexagon, topRightNeighbour);
            }
        }
    }
}

void Game::playerTurn()
{
    auto playerEdges = m_player->paintedEdges();
    auto computerEdges = m_computer->paintedEdges();

    for (auto& edge : playerEdges)
    {
        edge->thick();
    }
    for (auto& edge : computerEdges)
    {
        edge->thin();
    }
    m_window->run(m_graph, m_player, m_computer);
}

void Game::computerTurn()
{
    auto playerEdges = m_player->paintedEdges();
    auto computerEdges = m_computer->paintedEdges();

    for (auto& edge : computerEdges)
    {
        edge->thick();
    }
    for (auto& edge : playerEdges)
    {
        edge->thin();
    }
    m_computer->pickColor(m_player->chosenColor(), m_graph);
    m_window->render(m_graph);
    // Add a delay to observe the color change
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
}


