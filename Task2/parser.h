#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "lexical_analyzer.h"

struct Node;
typedef shared_ptr<Node> node_ptr;

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
    node_ptr parse_type_name();
    node_ptr parse_var_list();
    node_ptr parse_var_list_continue();
    node_ptr parse_var();
    node_ptr parse_var_name();
    string get_name();
};

#endif //PARSER_H
