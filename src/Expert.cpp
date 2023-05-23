#include "Expert.h"

void Expert::pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph)
{
    auto maxGain = 0;
    auto totalGain = 0;

    checkAvailableColors(playerColor);
    auto firstTurn = m_availableColors;
    sf::Color originalColor = m_currentColor;

    for (auto firstColor : firstTurn)
    {
        auto original = m_paintedEdges;
        // pick first color
        setChosenColor(*firstColor);

        for (auto& edge : m_paintedEdges)
        {
            edge->setColor(maxColor);
        }

        // check colors after picking first color (neighbours of neighbours)
        totalGain += checkGain(playerColor, graph);

        if (totalGain > maxGain)
        {
            maxGain = totalGain;
            bestChoice = *firstColor;
        }

        // go back to original so we can pick next color
        setChosenColor(originalColor);

        for (auto& edge : m_paintedEdges)
        {
            edge->setColor(originalColor);
        }
        m_paintedEdges = original;
        std::cout << totalGain << std::endl;
        totalGain = 0;
    }
    // prepare for DFS
    auto visited = graph->getVisited();
    setChosenColor(bestChoice); 

    /*for (auto& edge : m_paintedEdges)
    {
        edge->setColor(bestChoice);
    }*/

    // perform DFS to get all neighbors with the chosen color
    graph->DFS(m_startingPoint, bestChoice, m_paintedEdges, visited);

    for (auto& edge : m_paintedEdges)
    {
        edge->setColor(bestChoice);
    }
    //auto choice = checkGain(playerColor, graph);
    
    //std::cout << totalGain << std::endl;

    // Update control
    float newControl = static_cast<float>(m_paintedEdges.size()) / static_cast<float>(graph->getEdges().size());
    setControl(newControl);
}




int Expert::checkGain(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph)
{
    checkAvailableColors(playerColor);

    int maxSizeIncrease = 0;
    std::unordered_set<std::shared_ptr<Shape>> highestSize;

    for (const auto& color : m_availableColors)
    {
        // prepare for DFS
        auto visited = graph->getVisited();
        std::unordered_set<std::shared_ptr<Shape>> newSize = m_paintedEdges;

        // paint owned edges
        for (auto& edge : m_paintedEdges)
        {
            edge->setColor(*color);
        }

        // perform DFS to get all neighbors with the chosen color
        graph->DFS(m_startingPoint, *color, newSize, visited);

        int sizeIncrease = newSize.size() - m_paintedEdges.size();

        if (sizeIncrease > maxSizeIncrease)
        {
            maxSizeIncrease = sizeIncrease;
            maxColor = *color;
            highestSize = newSize;
        }
    }
    //m_paintedEdges = highestSize;
    //setChosenColor(maxColor); 

    /*for (auto& edge : m_paintedEdges)
    {
        edge->setColor(maxColor);
    }*/

    return maxSizeIncrease;
}

void Expert::checkAvailableColors(const sf::Color playerColor)
{
	m_availableColors.clear();

	for (int i = 0; i < m_colors().size(); i++)
	{
		if (m_colors[i] != playerColor &&
			m_colors[i] != chosenColor())
		{
			m_availableColors.push_back(std::make_shared<sf::Color>(m_colors[i]));
		}
	}
}
