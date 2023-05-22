#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics/Color.hpp>

template <typename T>
class Graph {
public:
    /*--------------------------------*\
   |----------- CONSTRUCTOR ------------|
    \*--------------------------------*/
     
    // create an empty graph
    Graph() {}

    /*--------------------------------*\
   |------------ FUNCTIONS -------------|
    \*--------------------------------*/

    std::shared_ptr<T> addEdge(std::shared_ptr<T> edge)
    {
        // If it's the first edge, make it the root
        if (m_edges.empty())
        {
            m_edges[edge] = {}; // Initialize edge's neighbour list
            m_root = edge;
        }
        else
        {
            m_edges[edge] = {}; // Initialize edge's neighbour list
        }

        m_visited[edge] = false;
        return edge;
    }


    // links two edges
    void addNeighbour(const std::shared_ptr<T>& v, const std::shared_ptr<T>& w)
    {
        m_edges[v].insert(w);
        m_edges[w].insert(v);
    }

    // get a vector of the graph's edges
    std::vector<std::shared_ptr<T>> getEdges()
    {
        std::vector<std::shared_ptr<T>> edgesVector;
        edgesVector.reserve(m_edges.size());

        for (const auto& edge : m_edges)
        {
            edgesVector.push_back(edge.first);
        }

        return edgesVector;
    }

    // set a pointer of the graph's root
    void setRoot(std::shared_ptr<T> root)
    {
        m_root = root;
    }

    // get a pointer of the graph's root
    std::shared_ptr<T> getRoot()
    {
        return m_root;
    }

    // randomize the colors of every edge in the graph
    void randomizeColors()
    {
        for (auto& edge : m_edges)
        {
            edge.first->randomColor();
        }
    }

    // need a clean visited map for every DFS run
    std::unordered_map<std::shared_ptr<T>, bool> getVisited()
    {
        return m_visited;
    }

    // return graph's neighbours with the same color
    std::unordered_set<std::shared_ptr<T>> DFS(const std::shared_ptr<T>& v, const sf::Color& targetColor, std::unordered_map<std::shared_ptr<T>, bool>& visited)
    {
        std::unordered_set<std::shared_ptr<T>> neighbours;

        // check if already visited this edge
        if (visited[v] || v->getColor() != targetColor)
        {
            return neighbours;  // Node already visited, return empty vector
        }
        visited[v] = true;

        // check if this edge has the target color
        if (v->getColor() == targetColor)
        {
            neighbours.insert(v);

            for (const auto& edge : m_edges[v])
            {
                auto edgeNeighbours = DFS(edge, targetColor, visited);
                neighbours.insert(edgeNeighbours.begin(), edgeNeighbours.end());
                
            }
        }

        visited[v] = false;

        return neighbours;
    }

private:
    // edges + their adjacency list (neighbours)
    std::unordered_map<std::shared_ptr<T>, std::unordered_set<std::shared_ptr<T>>> m_edges; 
    std::unordered_map<std::shared_ptr<T>, bool> m_visited;   // for DFS
    std::shared_ptr<T> m_root;  // graph's root
};