#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <iostream>
#include "parser_exception.h"

enum token {
    BEGIN, NAME, SIZE, STAR, COMMA, SEMICOLON, END
};

struct lexical_analyzer {

    lexical_analyzer();
    explicit lexical_analyzer(const string& in);

    void next_token();

    size_t get_cur_pos();
    token get_cur_token();
    string get_cur_token_string();

private:

    string s;
    size_t cur_pos;
    token cur_token;
    size_t cur_token_length;

    void inc_pos(size_t x);

    bool is_blank(size_t pos);
    bool is_letter(size_t pos);
    bool is_number(size_t pos);
    bool is_end_of_size(size_t pos);
    bool is_end(size_t pos);
};

#endif //LEXICAL_ANALYZER_H
