#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "utils.h"

Token* parse_query(const char* query) {

    printf("Parsing query: %s\n", query);
    int word_count = 0;
    char** words = split_string(query, ' ', &word_count);

    for (int i = 0; i < word_count; i++) {
        printf("Word %d: %s\n", i, words[i]);
        free(words[i]);
    }
    free(words);

    // Simple placeholder implementation for parsing
    Token* root = (Token*)malloc(sizeof(Token));
    root->type = TOKEN_ROOT;
    root->value = NULL;
    root->children = NULL;
    root->children_count = 0;
    return root;
}