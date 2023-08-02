#pragma once

#include "Graph.h"

template <typename NodeType>
class Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Node<NodeType>;
    using difference_type = std::ptrdiff_t;
    using pointer = Node<NodeType>*;
    using reference = Node<NodeType>&;

    Iterator(Graph<NodeType>& graph)
        : m_graph(graph), m_node(&graph.getNode(0)), m_index(0) {}
    Iterator(Graph<NodeType>& graph, size_t index)
        : m_graph(graph), m_node(&graph.getNode(0)), m_index(index) {}
    Iterator(Graph<NodeType>& graph, Node<NodeType>* node)
        : m_graph(graph), m_node(node), m_index(0) {}
    Iterator(Graph<NodeType>& graph, Node<NodeType>* node, size_t index)
        : m_graph(graph), m_node(node), m_index(index) {}

    reference operator*()
    {
        return *(m_node + m_index);
    }

    pointer operator->() {
        return &(*(m_graph.begin() + m_index));
    }

    Iterator& operator++()
    {
        ++m_index;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator temp(*this);
        ++(*this);
        return temp;
    }

    Iterator operator+(size_t other) const {
        Iterator result = *this;
        result.m_index += other;
        return result;
    }

    bool operator==(const Iterator& other) const
    {
        return m_node == other.m_node && m_index == other.m_index;
    }

    bool operator!=(const Iterator& other) const
    {
        return !(*this == other);
    }

private:
    Graph<NodeType>& m_graph;
    pointer m_node;
    size_t m_index;
};

template <typename NodeType>
class ConstIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = const Node<NodeType>;
    using difference_type = std::ptrdiff_t;
    using pointer = const Node<NodeType>*;
    using reference = const Node<NodeType>&;

    ConstIterator(const Graph<NodeType>& graph)
        : m_graph(graph), m_node(&graph.getNode(0)), m_index(0) {}
    ConstIterator(const Graph<NodeType>& graph, size_t index)
        : m_graph(graph), m_node(&graph.getNode(0)), m_index(index) {}
    ConstIterator(const Graph<NodeType>& graph, Node<NodeType>* node)
        : m_graph(graph), m_node(node), m_index(0) {}
    ConstIterator(const Graph<NodeType>& graph, Node<NodeType>* node, size_t index)
        : m_graph(graph), m_node(node), m_index(index) {}

    reference operator*()
    {
        return *(m_node + m_index);
    }

    pointer operator->() {
        return &(*(m_graph.begin() + m_index));
    }

    ConstIterator& operator++()
    {
        ++m_index;
        return *this;
    }

    ConstIterator operator++(int)
    {
        ConstIterator temp(*this);
        ++(*this);
        return temp;
    }

    ConstIterator operator+(int other) const {
        ConstIterator result = *this;
        result.m_index += other;
        return result;
    }

    bool operator==(const ConstIterator& other) const
    {
        return m_node == other.m_node && m_index == other.m_index;
    }

    bool operator!=(const ConstIterator& other) const
    {
        return !(*this == other);
    }

private:
    Graph<NodeType> m_graph;
    const pointer m_node;
    size_t m_index;
};