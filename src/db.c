#include <stdlib.h> // For NULL
#include "db.h"
#include "table.h"

void example_db_data(DB* db) {
    // Populate the database with example data: Clients and Orders tables
    Schema clients_table = {0};
    clients_table.name = "Clients";
    Schema orders_table = {0};
    orders_table.name = "Orders";

    // Add both tables to the database
    db->tables = (Table*)malloc(2 * sizeof(Table));
    db->tables[0] = (Table){.schema = clients_table, .rows = NULL, .row_count = 0};
    db->tables[1] = (Table){.schema = orders_table, .rows = NULL, .row_count = 0};

    // Add columns and rows to Clients table
    add_column(&db->tables[0], "ID", TYPE_INT);
    add_column(&db->tables[0], "Name", TYPE_STRING);
    Row client_row1;
    client_row1.values = (void**)malloc(2 * sizeof(void*));
    client_row1.values[0] = (void*)malloc(sizeof(int));
    client_row1.values[1] = (void*)malloc(50 * sizeof(char));
    *(int*)client_row1.values[0] = 1;
    snprintf((char*)client_row1.values[1], 50, "Alice");
    add_row(&db->tables[0], client_row1);
    Row client_row2;
    client_row2.values = (void**)malloc(2 * sizeof(void*));
    client_row2.values[0] = (void*)malloc(sizeof(int));
    client_row2.values[1] = (void*)malloc(50 * sizeof(char));
    *(int*)client_row2.values[0] = 2;
    snprintf((char*)client_row2.values[1], 50, "Bob");
    add_row(&db->tables[0], client_row2);

    // Add columns and rows to Orders table
    add_column(&db->tables[1], "OrderID", TYPE_INT);
    add_column(&db->tables[1], "ClientID", TYPE_INT);
    Row order_row1;
    order_row1.values = (void**)malloc(2 * sizeof(void*));
    order_row1.values[0] = (void*)malloc(sizeof(int));
    order_row1.values[1] = (void*)malloc(sizeof(int));
    *(int*)order_row1.values[0] = 101;
    *(int*)order_row1.values[1] = 1;
    add_row(&db->tables[1], order_row1);
    Row order_row2;
    order_row2.values = (void**)malloc(2 * sizeof(void*));
    order_row2.values[0] = (void*)malloc(sizeof(int));
    order_row2.values[1] = (void*)malloc(sizeof(int));
    *(int*)order_row2.values[0] = 102;
    *(int*)order_row2.values[1] = 2;
    add_row(&db->tables[1], order_row2);

}

void init_db(DB* db) {
    db->tables = NULL;
}

void free_db(DB* db) {
    // Free tables and other resources associated with the DB
}