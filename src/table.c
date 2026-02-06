#include "table.h"

void add_column(Table* table, const char* column_name, DataType data_type) {
    // Check if the table doesn't have a column with the same name
    for (int i = 0; i < table->schema.column_count; i++) {
        if (strcmp(table->schema.columns[i].name, column_name) == 0) {
            // Column with the same name exists, do not add
            return;
        }
    }

    table->schema.columns = realloc(table->schema.columns, sizeof(Column) * (table->schema.column_count + 1));
    table->schema.columns[table->schema.column_count].name = strdup(column_name);
    table->schema.columns[table->schema.column_count].type = data_type;
    table->schema.columns[table->schema.column_count].id = table->schema.column_count;
    table->schema.column_count++;
}

void add_row(Table* table, Row row) {
    table->rows = realloc(table->rows, sizeof(Row) * (table->row_count + 1));
    table->rows[table->row_count] = row;
    table->row_count++;
}

void table_to_string(const Table* table, char* buffer, size_t buffer_size, size_t cell_size) {
    size_t used = 0;

    for (int i = 0; i < table->row_count; i++) {
        for (int j = 0; j < table->schema.column_count; j++) {
            DataType data_type = table->schema.columns[j].type;
            const char* value = convert_data_type_to_string(
                (const char*)table->rows[i].values[j], data_type, cell_size
            );
            int written = snprintf(buffer + used, buffer_size - used, "%s", value);
            if (written < 0 || (size_t)written >= buffer_size - used) {
                // Buffer overflow or encoding error
                return;
            }
            used += written;

            if (j < table->schema.column_count - 1) {
                if (used < buffer_size - 1) {
                    buffer[used++] = ',';
                } else {
                    return;
                }
            }
        }
        if (i < table->row_count - 1) {
            if (used < buffer_size - 1) {
                buffer[used++] = '\n';
            } else {
                return;
            }
        }
    }
}