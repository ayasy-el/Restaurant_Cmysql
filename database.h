#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

void connect_db(MYSQL *conn);
void disconnect_db(MYSQL *conn);
void execute_query(MYSQL *conn, const char *query);

#endif
