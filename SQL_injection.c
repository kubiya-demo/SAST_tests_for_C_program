/*
    FIXED: Demonstrates secure SQL query execution using prepared statements.
    
    Previously: Executed user input directly as SQL without sanitization.
    Now: Uses parameterized queries (prepared statements) to prevent SQL injection.
    
    CWE-89: Improper Neutralization of Special Elements used in an SQL Command
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/*
    This callback function is tailor made for what SQLite expects.
*/
int callback(void *data, int argc, char **argv, char **azColName) {
    int *count = (int*)data;
    *count = atoi(argv[0]);
    return 0;
}


int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Create a dummy table and insert a row
    char *sql = "CREATE TABLE Users(Id INT, Name TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Insert one row
    sql = "INSERT INTO Users(Id, Name) VALUES(1, 'Alice')";
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    // Verify row count
    int rowCount = 0;
    sql = "SELECT COUNT(*) FROM Users;";
    rc = sqlite3_exec(db, sql, callback, &rowCount, &err_msg);
    if (rc != SQLITE_OK || rowCount != 1) {
        fprintf(stderr, "Unexpected row count or error\n");
        sqlite3_close(db);
        return 1;
    }

    printf("Initial user count: %d\n", rowCount);

    // FIXED: Use prepared statements to safely handle user input
    char user_name[256];
    int user_id;
    
    printf("Enter user ID: ");
    if (scanf("%d", &user_id) != 1) {
        fprintf(stderr, "Invalid input\n");
        sqlite3_close(db);
        return 1;
    }
    
    printf("Enter user name: ");
    scanf("%255s", user_name);  // Limit input size

    // Prepare statement with placeholders (?)
    sqlite3_stmt *stmt;
    sql = "INSERT INTO Users(Id, Name) VALUES(?, ?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Bind parameters safely - SQL injection is now impossible
    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, user_name, -1, SQLITE_STATIC);

    // Execute the prepared statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("User added safely using prepared statement\n");
    }

    sqlite3_finalize(stmt);

    // Verify final row count
    rowCount = 0;
    sql = "SELECT COUNT(*) FROM Users;";
    rc = sqlite3_exec(db, sql, callback, &rowCount, &err_msg);
    printf("Final user count: %d\n", rowCount);

    sqlite3_close(db);
    return 0;
}
