#include "lexical_analyzer.h"

lexical_analyzer::lexical_analyzer() : s(), cur_pos(0), cur_token(BEGIN), cur_token_length(0) {};

lexical_analyzer::lexical_analyzer(const string& in) : s(in), cur_pos(0), cur_token(BEGIN), cur_token_length(0) {};

bool lexical_analyzer::is_blank(size_t pos) {
    return s[pos] == ' ' || s[pos] == '\r' || s[pos] == '\n' || s[pos] == '\t';
}

bool lexical_analyzer::is_letter(size_t pos) {
    return (s[pos] >= 'a' && s[pos] <= 'z') || (s[pos] >= 'A' && s[pos] <= 'Z');
}

bool lexical_analyzer::is_last(size_t pos) {
    return pos == s.size() - 1;
}

void lexical_analyzer::inc_pos(size_t x) {
    cur_pos += x;
    if (cur_pos >= s.size()) {
        throw parser_exception("Out of string range");
    }
}

void lexical_analyzer::next_token() {
    inc_pos(cur_token_length);
    while (is_blank(cur_pos)) {
        inc_pos(1);
    }
    cur_token_length = 1;
    switch (s[cur_pos]) {
        case '*':
            cur_token = STAR;
            break;
        case ',':
            cur_token = COMMA;
            break;
        case ';':
            cur_token = SEMICOLON;
            break;
        case '$':
            cur_token = END;
            break;
        default:
            if (is_letter(cur_pos)) {
                cur_token = NAME;
                while (!is_last(cur_pos + cur_token_length - 1) && is_letter(cur_pos + cur_token_length)) {
                    ++cur_token_length;
                }
            } else {
                throw parser_exception("Illegal character", cur_pos);
            }
    }
}

size_t lexical_analyzer::get_cur_pos() {
    return cur_pos;
}

token lexical_analyzer::get_cur_token() {
    return cur_token;
}

string lexical_analyzer::get_cur_token_string() {
    return string(s, cur_pos, cur_token_length);
}