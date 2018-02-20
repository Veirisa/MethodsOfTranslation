#include "visualizer.h"

visualizer::visualizer(node_ptr root) : number(1), fout("tree.dot") {
    fout << "digraph {\n";
    recursive_visualize(root);
    fout << "}";
};

size_t visualizer::recursive_visualize(node_ptr node) {
    size_t cur_number = number;
    fout << cur_number << "[label = \"" << node->str << "\"]\n";
    ++number;
    for (size_t i = 0; i < node->children.size(); ++i) {
        size_t child_number = recursive_visualize(node->children[i]);
        fout << cur_number << " -> " << child_number <<";\n";

    }
    return cur_number;
}