#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "schema.h"
#include "utils.h"

/**
 * @brief Converts a string to a token type, given multiple table schemas.
 * 
 * @param str The string to convert (e.g. `"SELECT"`, `"Clients.Name"`, `"="`, etc.)
 * @param schemas An array of table schemas to consider for column and table names.
 * @param schema_count The number of schemas in the array.
 * @return int TokenType corresponding to the string, or TOKEN_VALUE if it's not a recognized keyword or token type.
 */
int str_to_token_type(const char* str, Schema* schemas, int schema_count) {
    if (strcmp(str, "SELECT") == 0) return TOKEN_SELECT;
    if (strcmp(str, "FROM") == 0) return TOKEN_FROM;
    if (strcmp(str, "JOIN") == 0) return TOKEN_JOIN;
    if (strcmp(str, "ON") == 0) return TOKEN_ON;
    if (strcmp(str, "WHERE") == 0) return TOKEN_WHERE;

    // Check if it's a table name
    for (int i = 0; i < schema_count; i++) {
        if (strcmp(str, schemas[i].name) == 0) {
            return TOKEN_TABLE;
        }
        // Check if it's a column name in the format "Table.Column"
        for (int j = 0; j < schemas[i].column_count; j++) {
            char full_column_name[256];
            snprintf(full_column_name, sizeof(full_column_name), "%s.%s", schemas[i].name, schemas[i].columns[j].name);
            if (strcmp(str, full_column_name) == 0) {
                return TOKEN_COLUMN;
            }
        }
    }

    return TOKEN_VALUE; // Default to value if not a keyword or recognized table/column
}

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_ROOT: return "ROOT";
        case TOKEN_TABLE: return "TABLE";
        case TOKEN_COLUMN: return "COLUMN";
        case TOKEN_VALUE: return "VALUE";
        case TOKEN_SELECT: return "SELECT";
        case TOKEN_FROM: return "FROM";
        case TOKEN_JOIN: return "JOIN";
        case TOKEN_ON: return "ON";
        case TOKEN_WHERE: return "WHERE";
        default: return "UNKNOWN";
    }
}

static inline char* trim_comma_at_end(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == ',') {
        str[len - 1] = '\0';
    }
    return str;
}

/**
 * @brief Parses a SQL query string into a simple token tree.
 * 
 * @param query The SQL query string to parse.
 * @return Token* A pointer to the root token of the parsed query tree.
 * 
 * @example
 * const char* query = "SELECT Clients.Name, Orders.OrderID "
 * "FROM Clients JOIN Orders ON Clients.ID = Orders.ClientID;"
 * 
 * Token* root = parse_query(query);
 * 
 * Then the tree structure would be:
 * > TOKEN_ROOT
 * >> TOKEN_SELECT (value: "SELECT")
 * >>> TOKEN_COLUMN (value: "Clients.Name")
 * >>> TOKEN_COLUMN (value: "Orders.OrderID")
 * >> TOKEN_FROM (value: "FROM")
 * >>> TOKEN_TABLE (value: "Clients")
 * >> TOKEN_JOIN (value: "JOIN")
 * >>> TOKEN_TABLE (value: "Orders")
 * >> TOKEN_ON (value: "ON")
 * >>> TOKEN_COLUMN (value: "Clients.ID")
 * >>> TOKEN_COLUMN (value: "Orders.ClientID")
 */
Token* parse_query(const char* query, Schema* schemas, int schema_count) {
    int word_count = 0;
    char** words = split_string(query, ' ', &word_count);

    Token* root = malloc(sizeof(Token));
    root->type = TOKEN_ROOT;
    root->value = NULL;
    root->children = NULL;
    root->children_count = 0;

    Token* current_clause = NULL;

    for (int i = 0; i < word_count; i++) {
        char* word = trim_comma_at_end(words[i]);

        // Skip empty tokens
        if (strlen(word) == 0) continue;
        if (strcmp(word, "=") == 0) continue;

        int token_type = str_to_token_type(word, schemas, schema_count);

        Token* token = malloc(sizeof(Token));
        token->type = token_type;
        token->value = strdup(word);
        token->children = NULL;
        token->children_count = 0;

        // Clause starters become direct children of root
        if (token_type == TOKEN_SELECT ||
            token_type == TOKEN_FROM ||
            token_type == TOKEN_JOIN ||
            token_type == TOKEN_ON ||
            token_type == TOKEN_WHERE) {

            root->children = realloc(
                root->children,
                sizeof(Token*) * (root->children_count + 1)
            );

            root->children[root->children_count++] = token;
            current_clause = token;
        }
        // Everything else becomes a child of the current clause
        else if (current_clause) {
            current_clause->children = realloc(
                current_clause->children,
                sizeof(Token*) * (current_clause->children_count + 1)
            );

            current_clause->children[current_clause->children_count++] = token;
        }
        // Fallback: attach to root if no clause exists yet
        else {
            root->children = realloc(
                root->children,
                sizeof(Token*) * (root->children_count + 1)
            );

            root->children[root->children_count++] = token;
        }
    }

    // Cleanup
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    return root;
}

void token_to_string(Token* token, char* buffer, size_t buffer_size, int indent_level) {
    if (!token || !buffer) return;

    const char* type_str = token_type_to_string(token->type);

    char indent[64] = {0};
    for (int i = 0; i < indent_level && i < sizeof(indent) - 1; i++) {
        strcat(indent, "  ");
    }

    snprintf(buffer + strlen(buffer), buffer_size - strlen(buffer), "%s%s", indent, type_str);
    if (token->value) {
        snprintf(buffer + strlen(buffer), buffer_size - strlen(buffer), "(%s)", token->value);
    }
    snprintf(buffer + strlen(buffer), buffer_size - strlen(buffer), "\n");

    for (int i = 0; i < token->children_count; i++) {
        token_to_string(token->children[i], buffer, buffer_size, indent_level + 1);
    }
}