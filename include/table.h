#ifndef TABLE_H
#define TABLE_H

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
    void** values; // Array of pointers to hold values of different types
} Row;

typedef struct {
    char* name;
    Column* columns;
    int column_count;
    Row* rows;
    int row_count;
} Table;

void add_column(Table* table, const char* column_name, DataType data_type);

void add_row(Table* table, Row row);

void table_to_string(const Table* table, char* buffer, size_t buffer_size, size_t cell_size);

#endif