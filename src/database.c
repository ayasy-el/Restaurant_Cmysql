#include "database.h"

#include <stdio.h>
#include <stdlib.h>

void connect_db(MYSQL *conn) {
    mysql_init(conn);
    if (mysql_real_connect(conn, "localhost", "root", getenv("DBPassword"), "restoran_db", 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
}

void disconnect_db(MYSQL *conn) {
    mysql_close(conn);
}

void execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
}

MYSQL_RES *fetch_query(MYSQL *conn, const char *query) {
    execute_query(conn, query);
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return result;
}