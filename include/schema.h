#ifndef SCHEMA_H
#define SCHEMA_H

#include <stddef.h> // For size_t

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} DataType;

const char* convert_data_type_to_string(const char* data, DataType data_type, size_t cell_size);


typedef struct {
    int id;
    char* name;
    DataType type;
} Column;

typedef struct {
    char* name;
    Column* columns;
    int column_count;
} Schema;

#endif // SCHEMA_H