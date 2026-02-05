#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static char *string_duplicate(const char *str) {
    if (!str) {
        return NULL;
    }
    size_t length = strlen(str) + 1;
    char *copy = malloc(length);
    if (!copy) {
        return NULL;
    }
    memcpy(copy, str, length);
    return copy;
}

static void free_split_result(char **result, int tokens) {
    if (!result) {
        return;
    }
    for (int i = 0; i < tokens; i++) {
        free(result[i]);
    }
    free(result);
}

int starts_with(const char* str, const char* prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;    
}

char **split_string(const char *str, char delimiter, int *count) {
    char **result = NULL;
    printf ("Splitting string: %s by delimiter: %c\n", str, delimiter);
    if (!count) {
        return NULL;
    }
    *count = 0;
    if (!str) {
        return NULL;
    }
    char *temp = string_duplicate(str);   // Copy because strtok modifies the string
    if (!temp) {
        return NULL;
    }
    printf("Temporary string for tokenization: %s\n", temp);
    char delim[2] = { delimiter, '\0' };
    char *token;
    int tokens = 0;

    token = strtok(temp, delim);
    while (token) {
        char **next = realloc(result, sizeof(char *) * (tokens + 1));
        if (!next) {
            free(temp);
            free_split_result(result, tokens);
            return NULL;
        }
        result = next;
        result[tokens] = string_duplicate(token);
        if (!result[tokens]) {
            free(temp);
            free_split_result(result, tokens);
            return NULL;
        }
        tokens++;
        token = strtok(NULL, delim);
    }

    free(temp);
    *count = tokens;
    return result;
}
