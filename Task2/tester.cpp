#include "parser.h"

void get_from_tree(string& s, node_ptr node) {
    if (node->children.empty()) {
        if (node->str != "DESCR_LIST'" && node->str != "VAR_LIST'")
        s.append(node->str);
    } else {
        for (size_t i = 0; i < node->children.size(); ++i) {
            get_from_tree(s, node->children[i]);
        }
    }
}

string delete_blanks(const string& s) {
    string result;
    bool need_type_blank = true;
    bool was_not_blank = false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == ' ' || s[i] == '\r' || s[i] == '\n' || s[i] == '\t') {
            if (need_type_blank && was_not_blank) {
                need_type_blank = false;
                result += ' ';
            }
        } else {
            was_not_blank = true;
            result += s[i];
            if (need_type_blank && i < s.size() - 1 && s[i + 1] == '*') {
                need_type_blank = false;
                result += ' ';
            }
        }
        if (s[i] == ';') {
            need_type_blank = true;
            was_not_blank = false;
        }
    }
    return result;
}

const size_t TESTS_SIZE = 8;
const string test[8] =
        { "int aA;",
          "  int  aA   ; ",
          "long ***zZ;",
          " long   **   *  zZ;   ",
          "double**qQ,    **wW, Bb;",
          "    double  * *qQ   ,   *wW,* *  *   bBb    ;",
          "float qQ, *wW, ***bBb; float *****qQ, x, mm; int x, xx, xxx, xxxx, **d;",
          "    float  qQ,   * wW ,  * * * bBb;float* *  ***qQ, x, mm;    int x,xx,* xxx   , xxxx, * *d;  "
        };

int main() {
    parser test_parser;

    cout << "default tests: \n";
    for (size_t i = 0; i < TESTS_SIZE; ++i) {
        string tree_string;
        get_from_tree(tree_string, test_parser.parse(test[i]));
        cout << i << ": " << (tree_string == delete_blanks(test[i]) ? "OK" : "FAIL") << "\n";
    }

    cout << "\n" << "your test: \n\n";
    string test_string, tree_string;
    getline(cin, test_string);
    get_from_tree(tree_string, test_parser.parse(test_string));
    cout << (tree_string == delete_blanks(test_string) ? "OK" : "FAIL") << "\n";
    return 0;
}