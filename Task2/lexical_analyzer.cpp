#include "lexical_analyzer.h"

lexical_analyzer::lexical_analyzer() : s(), cur_pos(0) {};

lexical_analyzer::lexical_analyzer(const string& in) : s(in), cur_pos(0) {};

bool lexical_analyzer::cur_is_blank() {
    return s[cur_pos] == ' ' || s[cur_pos] == '\r' || s[cur_pos] == '\n' || s[cur_pos] == '\t';
}

bool lexical_analyzer::cur_is_letter() {
    return (s[cur_pos] >= 'a' && s[cur_pos] <= 'z') || (s[cur_pos] >= 'A' && s[cur_pos] <= 'Z');
}

void lexical_analyzer::next_pos() {
    ++cur_pos;
    if (cur_pos == s.size()) {
        throw parser_exception("Out of string range");
    }
}

size_t lexical_analyzer::get_cur_pos() {
    return cur_pos;
}

char lexical_analyzer::get_cur_char() {
    return s[cur_pos];
}

token lexical_analyzer::get_cur_token() {
    while(cur_is_blank()) {
        next_pos();
    }
    switch (s[cur_pos]) {
        case '*':
            return STAR;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        case '$':
            return END;
        default:
            if (cur_is_letter()) {
                return NAME;
            } else {
                throw parser_exception("Illegal character", cur_pos);
            }
    }
}