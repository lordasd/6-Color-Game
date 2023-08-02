#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Config.h"
#include <iostream>
#include "Node.h"

template<typename NodeType>
class Iterator;
template<typename NodeType>
class ConstIterator;

template<typename NodeType>
class Graph {
public:
    Graph();
    Node<NodeType>& getNode(size_t index);
    void insert(const Node<NodeType>& node);

    Iterator<NodeType> begin();
    Iterator<NodeType> end();
    ConstIterator<NodeType> cbegin() const;
    ConstIterator<NodeType> cend() const;

private:
	std::vector<Node<NodeType>> m_nodes;
    
};

template<typename NodeType>
inline Graph<NodeType>::Graph()
{
    // Reserve to insert without resizing
    m_nodes.reserve(BOARD_SIZE * BOARD_SIZE);
}

template<typename NodeType>
inline Node<NodeType>& Graph<NodeType>::getNode(size_t index)
{
    return *(m_nodes.begin() + index);
}

template<typename NodeType>
inline void Graph<NodeType>::insert(const Node<NodeType>& node)
{
    m_nodes.emplace_back(node);
}

template<typename NodeType>
Iterator<NodeType> Graph<NodeType>::begin() {
    return Iterator<NodeType>(*this);
}

template<typename NodeType>
Iterator<NodeType> Graph<NodeType>::end() {
    return Iterator<NodeType>(*this, m_nodes.size());
}

template<typename NodeType>
ConstIterator<NodeType> Graph<NodeType>::cbegin() const {
    return ConstIterator<NodeType>(*this);
}

template<typename NodeType>
ConstIterator<NodeType> Graph<NodeType>::cend() const {
    return ConstIterator<NodeType>(*this, m_nodes.size());
}