#include "commands.h"
#include "db.h"
#include "utils.h"

const char* handle_command(const char* command, DB* db) {
    if (starts_with(command, "SELECT")) {
        return handle_select_command(command, db);
    } else if (starts_with(command, "INSERT")) {
        return handle_insert_command(command, db);
    } else if (starts_with(command, "UPDATE")) {
        return handle_update_command(command, db);
    } else if (starts_with(command, "DELETE")) {
        return handle_delete_command(command, db);
    } else if (starts_with(command, "CREATE")) {
        return handle_create_command(command, db);
    } else if (starts_with(command, "DROP")) {
        return handle_drop_command(command, db);
    } else {
        return "Unknown command.";
    }
}

const char* handle_select_command(const char* command, DB* db) {
    // Implementation for SELECT command
    return "SELECT command executed.";
}

const char* handle_insert_command(const char* command, DB* db) {
    // Implementation for INSERT command
    return "INSERT command executed.";
}

const char* handle_update_command(const char* command, DB* db) {
    // Implementation for UPDATE command
    return "UPDATE command executed.";
}

const char* handle_delete_command(const char* command, DB* db) {
    // Implementation for DELETE command
    return "DELETE command executed.";
}

const char* handle_create_command(const char* command, DB* db) {
    // Implementation for CREATE command
    return "CREATE command executed.";
}

const char* handle_drop_command(const char* command, DB* db) {
    // Implementation for DROP command
    return "DROP command executed.";
}
