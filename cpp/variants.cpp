// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>
#include <variant>
#include <vector>

/// Inheritance Base
struct node_base {};
/// Inheritance A
struct node_a : public node_base {};
/// Inheritance B
struct node_b : public node_base {};
/// Inheritance C
struct node_c : public node_base {};

/// No inheritance D
struct node_d {};
/// No inheritance E
struct node_e {};
/// No inheritance F
struct node_f {};

using node_inherit = std::variant<node_a, node_b, node_c>;
using node_no_inherit = std::variant<node_d, node_e, node_f>;

/// Visitor can be reused!
struct visitor {
    // For inheritance.
    void operator()(const node_a&) { std::cout << "NodeA" << std::endl; }
    void operator()(const node_b&) { std::cout << "NodeB" << std::endl; }
    void operator()(const node_base&) { std::cout << "NodeBase" << std::endl; }

    // For non inheritance.
    void operator()(const node_d&) { std::cout << "NodeD" << std::endl; }
    void operator()(const node_e&) { std::cout << "NodeE" << std::endl; }

    // Even if NodeF is not present in the list, you cannot omit it.
    void operator()(const node_f&) { std::cout << "NodeF" << std::endl; }
};

int main() {
    std::vector<node_inherit> nodes_i = {node_a{}, node_b{}, node_c{},
                                         node_a{}};

    for (node_inherit& node : nodes_i) {
        std::visit(visitor{}, node);
    }

    std::cout << std::endl;
    std::vector<node_no_inherit> nodes_ni = {node_d{}, node_e{}};

    for (node_no_inherit& node : nodes_ni) {
        std::visit(visitor{}, node);
    }
}
