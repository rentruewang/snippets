// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>
#include <variant>
#include <vector>

/// Inheritance Base
struct NodeBase {};
/// Inheritance A
struct NodeA : public NodeBase {};
/// Inheritance B
struct NodeB : public NodeBase {};
/// Inheritance C
struct NodeC : public NodeBase {};

/// No inheritance D
struct NodeD {};
/// No inheritance E
struct NodeE {};
/// No inheritance F
struct NodeF {};

using NodesI = std::variant<NodeA, NodeB, NodeC>;
using NodesNI = std::variant<NodeD, NodeE, NodeF>;

/// Visitor can be reused!
struct Visitor {
    // For inheritance.
    void operator()(const NodeA&) { std::cout << "NodeA" << std::endl; }
    void operator()(const NodeB&) { std::cout << "NodeB" << std::endl; }
    void operator()(const NodeBase&) { std::cout << "NodeBase" << std::endl; }

    // For non inheritance.
    void operator()(const NodeD&) { std::cout << "NodeD" << std::endl; }
    void operator()(const NodeE&) { std::cout << "NodeE" << std::endl; }

    // Even if NodeF is not present in the list, you cannot omit it.
    void operator()(const NodeF&) { std::cout << "NodeF" << std::endl; }
};

int main() {
    std::vector<NodesI> nodes_i = {NodeA{}, NodeB{}, NodeC{}, NodeA{}};

    for (NodesI& node : nodes_i) {
        std::visit(Visitor{}, node);
    }

    std::cout << std::endl;
    std::vector<NodesNI> nodes_ni = {NodeD{}, NodeE{}};

    for (NodesNI& node : nodes_ni) {
        std::visit(Visitor{}, node);
    }
}
