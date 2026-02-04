#include "table.h"

const char* convert_data_type_to_string(const char* data, DataType data_type, size_t cell_size) {
    if (data_type == TYPE_INT) {
        static char buffer[32];
        snprintf(buffer, sizeof(buffer), "%d", *(int*)data);
        return buffer;
    } else if (data_type == TYPE_FLOAT) {
        static char buffer[32];
        snprintf(buffer, sizeof(buffer), "%.2f", *(float*)data);
        return buffer;
    } else if (data_type == TYPE_STRING) {
        static char buffer[256];
        snprintf(buffer, sizeof(buffer), "%.*s", (int)cell_size, data);
        return buffer;
    }
    return "";
}

void add_column(Table* table, const char* column_name, DataType data_type) {
    // Check if the table doesn't have a column with the same name
    for (int i = 0; i < table->column_count; i++) {
        if (strcmp(table->columns[i].name, column_name) == 0) {
            // Column with the same name exists, do not add
            return;
        }
    }

    table->columns = realloc(table->columns, sizeof(Column) * (table->column_count + 1));
    table->columns[table->column_count].name = strdup(column_name);
    table->columns[table->column_count].type = data_type;
    table->columns[table->column_count].id = table->column_count;
    table->column_count++;
}

void add_row(Table* table, Row row) {
    table->rows = realloc(table->rows, sizeof(Row) * (table->row_count + 1));
    table->rows[table->row_count] = row;
    table->row_count++;
}

void table_to_string(const Table* table, char* buffer, size_t buffer_size, size_t cell_size) {
    size_t used = 0;

    for (int i = 0; i < table->row_count; i++) {
        for (int j = 0; j < table->column_count; j++) {
            DataType data_type = table->columns[j].type;
            const char* value = convert_data_type_to_string(
                (const char*)table->rows[i].values[j], data_type, cell_size
            );
            int written = snprintf(buffer + used, buffer_size - used, "%s", value);
            if (written < 0 || (size_t)written >= buffer_size - used) {
                // Buffer overflow or encoding error
                return;
            }
            used += written;

            if (j < table->column_count - 1) {
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