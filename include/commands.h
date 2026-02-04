#ifndef COMMANDS_H
#define COMMANDS_H

#include "db.h"

const char* handle_command(const char* command, DB* db);

const char* handle_select_command(const char* command, DB* db);

const char* handle_insert_command(const char* command, DB* db);

const char* handle_update_command(const char* command, DB* db);

const char* handle_delete_command(const char* command, DB* db);

const char* handle_create_command(const char* command, DB* db);

const char* handle_drop_command(const char* command, DB* db);


#endif 