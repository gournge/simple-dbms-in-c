#include <stdlib.h>
#include "parser.h"

Token* parse_query(const char* query) {
    // Simple placeholder implementation for parsing
    Token* root = (Token*)malloc(sizeof(Token));
    root->type = TOKEN_ROOT;
    root->value = NULL;
    root->children = NULL;
    root->children_count = 0;
    return root;
}