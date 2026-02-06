#include "schema.h"

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