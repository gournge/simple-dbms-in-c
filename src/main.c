#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

const char* logo =
"   _____ _             ____  ____  __  __ ____  \n"
"  |_   _(_)_ __  _   _|  _ \\| __ )|  \\/  / ___| \n"
"    | | | | '_ \\| | | | | | | |_ \\| |\\/| \\___ \\ \n"
"    | | | | | | | |_| | |_| | |_) | |  | |___) |\n"
"    |_| |_|_| |_|\\__, |____/|____/|_|  |_|____/ \n"
"                 |___/                            \n"
"\n";


int main() {
    printf("%s", logo);
    printf("Welcome to the TinyDBMS!\n");

    char command[256];
    while(1) {
        printf("TinyDBMS> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; 
        }

        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            break;
        }

        char* result = handle_command(command);
        printf("%s\n", result);
    }

    printf("Exiting TinyDBMS. Goodbye!\n");
    
    return 0;
}