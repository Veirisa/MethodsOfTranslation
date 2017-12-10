#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "lexical_analyzer.h"

struct Node;
typedef Node* node_ptr;

struct Node {

    string str;
    vector<node_ptr> children;

    explicit Node(const string& s) : str(s) {};
};

struct parser {

    node_ptr parse(const string& s);

private:

    lexical_analyzer lex;

    node_ptr parse_descr_list();
    node_ptr parse_descr_list_continue();
    node_ptr parse_descr();
    node_ptr parse_var_list();
    node_ptr parse_var_list_continue();
    node_ptr parse_var();
    node_ptr parse_name(bool is_type);
};

#endif //PARSER_H
