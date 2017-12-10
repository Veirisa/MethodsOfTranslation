#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <fstream>
#import "parser.h"

struct visualizer {

    explicit visualizer(node_ptr root);

private:

    size_t number;
    ofstream fout;

    size_t recursive_visualize(bool is_left, node_ptr node);
};

#endif //VISUALIZER_H
