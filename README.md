# Simple DBMS in C

A minimal implementation of a DBMS supporting an SQL-like language in C.

Quick start: just run `make`.
    
Example usage:

    $ make
    gcc -Wall -Wextra -Iinclude -c src/db.c -o src/db.o
    gcc src/main.o src/commands.o src/db.o -o app
    $ ./app
    _____ _             ____  ____  __  __ ____  
    |_   _(_)_ __  _   _|  _ \| __ )|  \/  / ___| 
        | | | | '_ \| | | | | | | |_ \| |\/| \___ \ 
        | | | | | | | |_| | |_| | |_) | |  | |___) |
        |_| |_|_| |_|\__, |____/|____/|_|  |_|____/ 
                    |___/                            

    Welcome to the TinyDBMS!
    TinyDBMS> exit
    Exiting TinyDBMS. Goodbye!