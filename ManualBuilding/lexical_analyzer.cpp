#include "lexical_analyzer.h"

lexical_analyzer::lexical_analyzer() : s(), cur_pos(0), cur_token(BEGIN), cur_token_length(0) {};

lexical_analyzer::lexical_analyzer(const string& in) : s(in), cur_pos(0), cur_token(BEGIN), cur_token_length(0) {};

bool lexical_analyzer::is_blank(size_t pos) {
    return s[pos] == ' ' || s[pos] == '\r' || s[pos] == '\n' || s[pos] == '\t';
}

bool lexical_analyzer::is_letter(size_t pos) {
    return (s[pos] >= 'a' && s[pos] <= 'z') || (s[pos] >= 'A' && s[pos] <= 'Z');
}

bool lexical_analyzer::is_number(size_t pos) {
    return (s[pos] >= '0' && s[pos] <= '9');
}

bool lexical_analyzer::is_end_of_size(size_t pos) {
    return s[pos] == ']';
}

bool lexical_analyzer::is_end(size_t pos) {
    return pos == s.size();
}

void lexical_analyzer::inc_pos(size_t x) {
    cur_pos += x;
    if (cur_pos > s.size()) {
        throw parser_exception("Out of string range");
    }
}

void lexical_analyzer::next_token() {
    inc_pos(cur_token_length);
    while (is_blank(cur_pos)) {
        inc_pos(1);
    }
    cur_token_length = 1;
    if (is_end(cur_pos)) {
        cur_token = END;
        return;
    }
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
        case '[':
            cur_token = SIZE;
            while (!is_end(cur_pos + cur_token_length) && !is_end_of_size(cur_pos + cur_token_length) && is_number(cur_pos + cur_token_length)) {
                ++cur_token_length;
            }
            if (cur_token_length < 2 || !is_end_of_size(cur_pos + cur_token_length)) {
                throw parser_exception("Illegal token", cur_pos);
            }
            ++cur_token_length;
            break;
        default:
            if (is_letter(cur_pos)) {
                cur_token = NAME;
                while (!is_end(cur_pos + cur_token_length) && is_letter(cur_pos + cur_token_length)) {
                    ++cur_token_length;
                }
            } else {
                if (is_end_of_size(cur_pos) || is_number(cur_pos)) {
                    throw parser_exception("Illegal token", cur_pos);
                }
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
    if (cur_token == END) {
        throw parser_exception("Impossible to get string representation of the end");
    }
    return string(s, cur_pos, cur_token_length);
}