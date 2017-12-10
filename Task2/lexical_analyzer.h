#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <iostream>
#include "parser_exception.h"

enum token {
    NAME, STAR, COMMA, SEMICOLON, END
};

struct lexical_analyzer {

    lexical_analyzer();
    explicit lexical_analyzer(const string& in);

    void next_pos();
    size_t get_cur_pos();
    token get_cur_token();
    char get_cur_char();

    bool cur_is_letter();

private:

    string s;
    size_t cur_pos;

    bool cur_is_blank();
};


#endif //LEXICAL_ANALYZER_H
