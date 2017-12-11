#include "parser.h"

node_ptr parser::parse(const string& s) {
    lex = lexical_analyzer(s + '$');
    lex.next_token();
    return parse_descr_list();
};

node_ptr parser::parse_descr_list() {
    node_ptr node = make_shared<Node>(Node("DESCR_LIST"));
    switch (lex.get_cur_token()) {
        case NAME:
            node->children.push_back(parse_descr());
            node->children.push_back(parse_descr_list_continue());
            break;
        default:
            throw parser_exception("Wrong first of description list", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != END) {
        throw parser_exception("Wrong follow of description list", lex.get_cur_pos());
    }
    return node;
}

node_ptr parser::parse_descr_list_continue() {
    node_ptr node = make_shared<Node>(Node("DESCR_LIST'"));
    switch (lex.get_cur_token()) {
        case NAME:
            node->children.push_back(parse_descr());
            node->children.push_back(parse_descr_list_continue());
            break;
        case END:
            break;
        default:
            throw parser_exception("Wrong first of description list continue", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != END) {
        throw parser_exception("Wrong follow of description list continue", lex.get_cur_pos());
    }
    return node;
}

node_ptr parser::parse_descr() {
    node_ptr node = make_shared<Node>(Node("DESCR"));
    switch (lex.get_cur_token()) {
        case NAME:
            node->children.push_back(parse_type_name());
            node->children.push_back(parse_var_list());
            node->children.push_back(make_shared<Node>(Node(lex.get_token_string())));
            lex.next_token();
            break;
        default:
            throw parser_exception("Wrong first of desctiption", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != NAME && lex.get_cur_token() != END) {
        throw parser_exception("Wrong follow of description", lex.get_cur_pos());
    }
    return node;
}

node_ptr parser::parse_type_name() {
    node_ptr node = make_shared<Node>(Node("TYPE_NAME"));
    switch (lex.get_cur_token()) {
        case NAME:
            node->children.push_back(make_shared<Node>(Node(lex.get_token_string())));
            lex.next_token();
            break;
        default:
            throw parser_exception("Wrong first of type name", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != STAR && lex.get_cur_token() != NAME) {
        throw parser_exception("Wrong follow of type name", lex.get_cur_pos());
    }
    return node;
}

node_ptr parser::parse_var_list() {
    node_ptr node = make_shared<Node>(Node("VAR_LIST"));
    switch (lex.get_cur_token()) {
        case STAR:
        case NAME:
            node->children.push_back(parse_var());
            node->children.push_back(parse_var_list_continue());
            break;
        default:
            throw parser_exception("Wrong first of variables list", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != SEMICOLON) {
        throw parser_exception("Wrong follow of variables list", lex.get_cur_pos());
    }
    return node;
}

node_ptr parser::parse_var_list_continue() {
    node_ptr node = make_shared<Node>(Node("VAR_LIST'"));
    switch (lex.get_cur_token()) {
        case COMMA:
            node->children.push_back(make_shared<Node>(Node(lex.get_token_string())));
            lex.next_token();
            node->children.push_back(parse_var());
            node->children.push_back(parse_var_list_continue());
            break;
        case SEMICOLON:
            break;
        default:
            throw parser_exception("Wrong first of variables list continue", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != SEMICOLON) {
        throw parser_exception("Wrong follow of variables list continue", lex.get_cur_pos());
    }
    return node;
}

node_ptr parser::parse_var() {
    node_ptr node = make_shared<Node>(Node("VAR"));
    switch (lex.get_cur_token()) {
        case STAR:
            node->children.push_back(make_shared<Node>(Node(lex.get_token_string())));
            lex.next_token();
            node->children.push_back(parse_var());
            break;
        case NAME:
            node->children.push_back(parse_var_name());
            break;
        default:
            throw parser_exception("Wrong first of variable", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != COMMA && lex.get_cur_token() != SEMICOLON) {
        throw parser_exception("Wrong follow of variable", lex.get_cur_pos());
    }
    return node;
}

node_ptr parser::parse_var_name() {
    node_ptr node = make_shared<Node>(Node("VAR_NAME"));
    switch (lex.get_cur_token()) {
        case NAME:
            node->children.push_back(make_shared<Node>(Node(lex.get_token_string())));
            lex.next_token();
            break;
        default:
            throw parser_exception("Wrong first of variable name", lex.get_cur_pos());
    }
    if (lex.get_cur_token() != COMMA && lex.get_cur_token() != SEMICOLON) {
        throw parser_exception("Wrong follow of variable name", lex.get_cur_pos());
    }
    return node;
}