# Simple DBMS in C

A minimal implementation of a DBMS supporting an SQL-like language in C.

Quick start: just run `make`.
    
Example usage:

```
$ make
gcc src/main.o src/commands.o src/db.o src/utils.o src/table.o -o app
$ ./app
   _____ _             ____  ____  __  __ ____  
  |_   _(_)_ __  _   _|  _ \| __ )|  \/  / ___| 
    | | | | '_ \| | | | | | | |_ \| |\/| \___ \ 
    | | | | | | | |_| | |_| | |_) | |  | |___) |
    |_| |_|_| |_|\__, |____/|____/|_|  |_|____/ 
                 |___/                            

Welcome to the TinyDBMS!
Type your commands below. End each command with a semicolon (;).
Main commands: SELECT, INSERT, UPDATE, DELETE, CREATE, DROP.
Other commands: 'exit;' to quit the program. 'sample;' to clear db and add sample data.
TinyDBMS> sample;

Table: Clients
1,Alice
2,Bob

Table: Orders
101,1
102,2

TinyDBMS> exit;
Exiting TinyDBMS. Goodbye!
```

## Roadmap

### 1. Handling simple `SELECT` (and test build system)

Goal statements to be parsed:

```
SELECT
    customers.country,
FROM customers
JOIN orders ON orders.customer_id = c.id
WHERE orders.status = 'PAID';
```

### 2. Group by `SELECT`

```
SELECT
    c.country,
    COUNT(o.id) AS order_count,
    SUM(o.total_amount) AS revenue
FROM customers c
JOIN orders o ON o.customer_id = c.id
WHERE o.status = 'PAID'
GROUP BY c.country
HAVING SUM(o.total_amount) > 50000;
```