#ifndef PARSER_H
#define PARSER_H

#include "schema.h"

typedef enum {
    TOKEN_ROOT,
    TOKEN_TABLE,
    TOKEN_COLUMN,
    TOKEN_VALUE,
    TOKEN_SELECT,
    TOKEN_FROM,
    TOKEN_JOIN,
    TOKEN_ON,
    TOKEN_WHERE,
} TokenType;

int str_to_token_type(const char* str, Schema* schemas, int schema_count);

const char* token_type_to_string(TokenType type);

typedef struct {
    TokenType type;
    const char* value;
    struct Token** children;
    int children_count;
} Token;

void token_to_string(Token* token, char* buffer, size_t buffer_size, int indent_level);

Token* parse_query(const char* query, Schema* schemas, int schema_count);

#endif // PARSER_H