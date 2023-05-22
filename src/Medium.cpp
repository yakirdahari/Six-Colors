#include "Medium.h"

void Medium::pickColor(const sf::Color playerColor, std::shared_ptr<Graph<Shape>> graph)
{
    checkAvaiableColors(playerColor);

    int maxSizeIncrease = 0;
    sf::Color maxColor;
    std::unordered_set<std::shared_ptr<Shape>> maxPaintedEdges;

    for (const auto& color : m_availableColors)
    {
        // Prepare for DFS
        setChosenColor(*color);
        auto visited = graph->getVisited();

        std::unordered_set<std::shared_ptr<Shape>> oldPaintedEdges = m_paintedEdges;

        // Paint owned edges
        for (auto& edge : m_paintedEdges)
        {
            edge->setColor(chosenColor());
        }

        // Perform DFS to get all neighbors with the chosen color
        m_paintedEdges = graph->DFS(m_startingPoint, chosenColor(), visited);

        int sizeIncrease = m_paintedEdges.size() - oldPaintedEdges.size();

        if (sizeIncrease > maxSizeIncrease)
        {
            maxSizeIncrease = sizeIncrease;
            maxColor = chosenColor();
            maxPaintedEdges = m_paintedEdges;
        }

        // Revert m_paintedEdges back
        m_paintedEdges = oldPaintedEdges;
    }

    // Set the chosen color to the one with the largest size increase
    m_paintedEdges = maxPaintedEdges;
    for (auto& edge : m_paintedEdges)
    {
        edge->setColor(chosenColor());
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
