#include "visualizer.h"

void get_from_tree(bool is_type_name, string& s, node_ptr node) {
    if (node->children.empty()) {
        if (node->str.back() != '\'' && node->str != "ARRAY") {
            s += node->str;
            if (is_type_name) {
                s += ' ';
            }
        }
    } else {
        for (size_t i = 0; i < node->children.size(); ++i) {
            get_from_tree(node->str == "TYPE_NAME", s, node->children[i]);
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

//default tests:
const size_t TESTS_SIZE = 8;
const string default_test[TESTS_SIZE] =
        { "int aA;",
          "  int  \naA\n   \n; ",
          "long ***zZ;",
          " long   **\n\n*  zZ;   ",
          "double **qQ, **wW, Bb;",
          "    double* *qQ \n\n\n , \n  *wW,* *  *   bBb    ;",
          "float qQ, *wW, ***bBb; float *****qQ, x, mm; int x, xx, xxx, xxxx, **d;",
          "\n    float\n\nqQ,   * wW ,  * *\n * bBb;float* *  ***qQ, x, mm;  \n\n  int x,xx,* xxx   , xxxx, * *d;  \n\n"
        };

//test for visualisation:
const string test = "int a, *b, ***c, d;";
// const string test = "int a[3], **b, c; long **d[11];";

int main() {
    parser test_parser;

    cout << "default tests: \n";
    for (size_t i = 0; i < TESTS_SIZE; ++i) {
        string tree_string;
        get_from_tree(false, tree_string, test_parser.parse(default_test[i]));
        cout << i << ": " << (tree_string == delete_blanks(default_test[i]) ? "OK" : "FAIL") << "\n";
    }

    cout << "\n" << "test for visualization: \n";
    string tree_string;
    node_ptr root = test_parser.parse(test);
    get_from_tree(false, tree_string, root);
    cout << test << "\n" << (tree_string == delete_blanks(test) ? "OK" : "FAIL") << "\n";

    visualizer test_visualizer(root);

    return 0;
}