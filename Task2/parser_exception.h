#ifndef PARSER_EXCEPTION_H
#define PARSER_EXCEPTION_H

#include <exception>
using namespace std;

struct parser_exception : std::exception {
    const string message;

    const char *what() const throw() override {
        return message.c_str();
    }

    explicit parser_exception(const string& s) noexcept : message(s) {}
    explicit parser_exception(const string& s, size_t pos) noexcept : message(s + " on " + to_string(pos) + " position") {}
};

#endif //PARSER_EXCEPTION_H
