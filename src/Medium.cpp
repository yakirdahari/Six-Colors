#include "Medium.h"

void Medium::pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph)
{
    checkAvaiableColors(playerColor);

    int maxSizeIncrease = 0;
    sf::Color maxColor;

    for (const auto& color : m_availableColors)
    {
        // Prepare for DFS
        auto visited = graph->getVisited();
        std::unordered_set<std::shared_ptr<Shape>> newSize = m_paintedEdges;
        // Paint owned edges
        for (auto& edge : m_paintedEdges)
        {
            edge->setColor(*color);
        }

        // Perform DFS to get all neighbors with the chosen color
        graph->DFS(m_startingPoint, *color, newSize, visited);

        int sizeIncrease = newSize.size() - m_paintedEdges.size();
        std::cout << sizeIncrease << std::endl;

        if (sizeIncrease > maxSizeIncrease)
        {
            maxSizeIncrease = sizeIncrease;
            maxColor = *color;
            m_paintedEdges = newSize;
        }
        /*newSize.clear();*/
    }
    for (auto& edge : m_paintedEdges)
    {
        edge->setColor(maxColor);
    }

    // Update control
    float newControl = static_cast<float>(m_paintedEdges.size()) / static_cast<float>(graph->getEdges().size());
    setControl(newControl);

}

void Medium::checkAvaiableColors(const sf::Color playerColor)
{
	m_availableColors.clear();

	for (int i = 0 ; i < m_colors().size() ; i++)
	{
		if (m_colors[i] != playerColor &&
			m_colors[i] != chosenColor())
		{
			m_availableColors.push_back(std::make_shared<sf::Color>(m_colors[i]));
		}
	}
}
