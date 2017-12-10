#include "visualizer.h"

visualizer::visualizer(node_ptr root) : number(1), fout("tree.dot") {
    fout << "digraph {\n";
    recursive_visualize(true, root);
    fout << "}";
};

size_t visualizer::recursive_visualize(bool is_left, node_ptr node) {
    if (!is_left) {
        ++number;
    }
    size_t cur_number = number;
    if (node->children.empty()) {
        fout << cur_number << "[label = \"" << node->str << "\"]\n";
    }
    for (size_t i = 0; i < node->children.size(); ++i) {
        size_t child_number = recursive_visualize(i == 0, node->children[i]);
        if (i == 0) {
            cur_number = number;
            fout << cur_number << "[label = \"" << node->str << "\"]\n";
        }
        fout << cur_number << " -> " << child_number <<";\n";

    }
    if (is_left) {
        ++number;
    }
    return cur_number;
}