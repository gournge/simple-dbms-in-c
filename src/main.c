#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"
#include "commands.h"

const char* welcome =
"   _____ _             ____  ____  __  __ ____  \n"
"  |_   _(_)_ __  _   _|  _ \\| __ )|  \\/  / ___| \n"
"    | | | | '_ \\| | | | | | | |_ \\| |\\/| \\___ \\ \n"
"    | | | | | | | |_| | |_| | |_) | |  | |___) |\n"
"    |_| |_|_| |_|\\__, |____/|____/|_|  |_|____/ \n"
"                 |___/                            \n"
"\n"
"Welcome to the TinyDBMS!\n"
"Type your commands below. End each command with a semicolon (;).\n"
"Main commands: SELECT, INSERT, UPDATE, DELETE, CREATE, DROP.\n"
"Other commands: 'exit;' to quit the program. 'sample;' to clear db and add sample data.\n";

int main() {
    printf("%s", welcome);
    DB db = {0};
    char command[256];
    while(1) {
        printf("TinyDBMS> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; 
        }

        size_t len = strlen(command);
        if (len > 1 && command[len - 1] == '\n' && command[len - 2] == ';') {
            command[len - 1] = '\0';
        }

        if (strcmp(command, "sample;") == 0) {
            free_db(&db);
            init_db(&db);
            example_db_data(&db);
            // Iterate over tables and print their contents
            for (int i = 0; i < 2; i++) {
                char buffer[1024];
                table_to_string(&db.tables[i], buffer, sizeof(buffer), 50);
                printf("\nTable: %s\n%s\n", db.tables[i].name, buffer);
            }
            printf("\n");
            continue;
        }

        if (strcmp(command, "exit;") == 0) {
            break;
        }

        const char* result = handle_command(command, &db);
        printf("%s\n", result);
    }

    printf("Exiting TinyDBMS. Goodbye!\n");
    
    return 0;
}