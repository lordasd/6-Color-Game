#pragma once

#include <vector>

template<typename NodeType>
struct Node {
    Node() = default;
    Node(const NodeType& data);
    void insert(Node<NodeType>* node);

    NodeType m_node;
    std::vector<Node<NodeType>*> m_neighbors;
    bool visited = false;

};

template<typename NodeType>
inline Node<NodeType>::Node(const NodeType& data)
    : m_node(data) {}

template<typename NodeType>
inline void Node<NodeType>::insert(Node<NodeType>* node)
{
    m_neighbors.emplace_back(node);
}