#ifndef DB_H
#define DB_H

#include "table.h"

typedef struct {
    Table *tables;
} DB;

// Populate the database with example data 
void example_db_data(DB* db);

void init_db(DB* db);
void free_db(DB* db);

#endif