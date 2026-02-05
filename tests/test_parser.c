#include <assert.h>
#include <stdlib.h>
#include "parser.h"

void test_parser() {
    test_parse_query_non_null();
}

void test_parse_query_non_null() {
    const char* query = "SELECT * FROM Clients;";
    Token* root = parse_query(query);
    assert(root != NULL);
    assert(root->type == TOKEN_ROOT);
}

