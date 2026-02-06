#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "schema.h"

void test_parser() {
    test_parse_query_non_null();
    test_parse_query_columns_tables_values();
}

Schema* create_test_schemas(void) {
    static Column user_columns[] = {
        { 1, "id",   TYPE_INT },
        { 2, "name", TYPE_STRING }
    };

    static Column product_columns[] = {
        { 1, "price", TYPE_FLOAT }
    };

    static Schema schemas[] = {
        { "User", user_columns, 2 },
        { "Product", product_columns, 1 }
    };

    return schemas;
}


void test_parse_query_non_null() {
    const char* query = "SELECT * FROM Clients;";
    Token* root = parse_query(query, create_test_schemas(), 2);
    assert(root != NULL);
    assert(root->type == TOKEN_ROOT);
}

void test_parse_query_columns_tables_values() {
    const char* query = "SELECT Clients.Name, Orders.OrderID"
     " FROM Clients JOIN Orders ON Clients.ID = Orders.ClientID" 
     " WHERE Clients.ID = 1;";
    Token* root = parse_query(query, create_test_schemas(), 2);
    
    // Call token_to_string to visualize the tree structure
    char buffer[1024];
    token_to_string(root, buffer, sizeof(buffer), 0);
    printf("Parsed Token Tree:\n%s\n", buffer);

    assert(root != NULL);
    assert(root->type == TOKEN_ROOT);
}
