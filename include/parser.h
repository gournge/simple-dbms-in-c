#ifndef PARSER_H
#define PARSER_H

typedef enum {
    TOKEN_ROOT,
    TOKEN_TABLE,
    TOKEN_COLUMN,
    TOKEN_VALUE,
    TOKEN_SELECT,
    TOKEN_JOIN,
    TOKEN_WHERE,
} TokenType;

typedef struct {
    TokenType type;
    const char* value;
    struct Token** children;
    int children_count;
} Token;

Token* parse_query(const char* query);

#endif // PARSER_H