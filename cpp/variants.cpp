// Copyright (c) 2024 RenChu Wang - All Rights Reserved

#include <iostream>
#include <variant>
#include <vector>

using namespace std;

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

using node_inherit = variant<node_a, node_b, node_c>;
using node_no_inherit = variant<node_d, node_e, node_f>;

/// Visitor can be reused!
struct visitor {
    // For inheritance.
    void operator()(const node_a&) { cout << "NodeA" << endl; }
    void operator()(const node_b&) { cout << "NodeB" << endl; }
    void operator()(const node_base&) { cout << "NodeBase" << endl; }

    // For non inheritance.
    void operator()(const node_d&) { cout << "NodeD" << endl; }
    void operator()(const node_e&) { cout << "NodeE" << endl; }

    // Even if NodeF is not present in the list, you cannot omit it.
    void operator()(const node_f&) { cout << "NodeF" << endl; }
};

int main() {
    vector<node_inherit> nodes_i = {node_a{}, node_b{}, node_c{}, node_a{}};

    for (node_inherit& node : nodes_i) {
        visit(visitor{}, node);
    }

    cout << endl;
    vector<node_no_inherit> nodes_ni = {node_d{}, node_e{}};

    for (node_no_inherit& node : nodes_ni) {
        visit(visitor{}, node);
    }
}
