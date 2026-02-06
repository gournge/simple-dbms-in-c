#ifndef TABLE_H
#define TABLE_H

#include "schema.h" // For Schema

typedef struct {
    void** values; // Array of pointers to hold values of different types
} Row;

typedef struct {
    Schema schema;
    Row* rows;
    int row_count;
} Table;

void add_column(Table* table, const char* column_name, DataType data_type);

void add_row(Table* table, Row row);

void table_to_string(const Table* table, char* buffer, size_t buffer_size, size_t cell_size);

#endif