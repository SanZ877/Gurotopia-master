#include "pch.hpp"

#include "database.hpp"

MYSQL *db;

void create_table_if_not_exist()
{
    const char* query = R"(
        CREATE TABLE IF NOT EXISTS peer (
            uid INT AUTO_INCREMENT PRIMARY KEY,
            growid VARCHAR(18) UNIQUE,
            password VARCHAR(18),
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );
    )";
    
    /* world table */

    if (mysql_query(db, query))
    {
        fprintf(stderr, "%s\n", mysql_error(db));
    }
}

void mysql_connect()
{
    db = mysql_init(NULL);

    const char* db_host = getenv("DB_HOST") ? getenv("DB_HOST") : "db";
    const char* db_user = getenv("DB_USER") ? getenv("DB_USER") : "root";
    const char* db_pass = getenv("DB_PASS") ? getenv("DB_PASS") : "woigigawoi123";
    const char* db_name = getenv("DB_NAME") ? getenv("DB_NAME") : "gtps_db";

    int retry_count = 0;
    while (retry_count < 15)
    {
        if (mysql_real_connect(db, db_host, db_user, db_pass, db_name, 3306, NULL, 0))
        {
            printf("connected to SQL server on %s:%d\n", db_host, 3306);
            goto connected;
        }
        fprintf(stderr, "MySQL connection attempt %d failed: %s. Retrying in 2s...\n", retry_count + 1, mysql_error(db));
        sleep(2);
        retry_count++;
    }

    fprintf(stderr, "Could not connect to MySQL after 15 attempts. Exiting.\n");
    return;

connected:
    mysql_query(db, "CREATE DATABASE IF NOT EXISTS gurotopia");
    mysql_select_db(db, "gurotopia");

    create_table_if_not_exist();
}

hStmt::hStmt(const char *query)
{
    this->pStmt = mysql_stmt_init(db);
    if (!pStmt) 
    {
        fprintf(stderr, "%s\n", mysql_error(db));
    }
    if (mysql_stmt_prepare(pStmt, query, (u_long)strlen(query)))
    {
        fprintf(stderr, "%s\n", mysql_error(db));
    }
}
hStmt::~hStmt() 
{
    if (mysql_stmt_close(pStmt))
    {
        fprintf(stderr, "%s\n", mysql_error(db));
    }
}
MYSQL_BIND make_bind_in(const signed &buffer)
{
    return { .buffer = (void*)&buffer, .buffer_type = MYSQL_TYPE_LONG };
}
MYSQL_BIND make_bind_in(const unsigned &buffer)
{
    return { .buffer = (void*)&buffer, .buffer_type = MYSQL_TYPE_LONG, .is_unsigned = true };
}
MYSQL_BIND make_bind_in(const long &buffer)
{
    return { .buffer = (void*)&buffer, .buffer_type = MYSQL_TYPE_LONG };
}
MYSQL_BIND make_bind_in(const long long &buffer)
{
    return { .buffer = (void*)&buffer, .buffer_type = MYSQL_TYPE_LONGLONG };
}
MYSQL_BIND make_bind_in(const float &buffer)
{
    return { .buffer = (void*)&buffer, .buffer_type = MYSQL_TYPE_FLOAT };
}
MYSQL_BIND make_bind_in(const std::string &buffer)
{
    return { .buffer = (void*)buffer.c_str(), .buffer_length = (u_long)buffer.size(), .buffer_type = MYSQL_TYPE_STRING };
}

MYSQL_BIND make_bind_out(signed &buffer)
{
    return { .buffer = &buffer, .buffer_type = MYSQL_TYPE_LONG };
}
MYSQL_BIND make_bind_out(unsigned &buffer)
{
    return { .buffer = &buffer, .buffer_type = MYSQL_TYPE_LONG, .is_unsigned = true };
}
MYSQL_BIND make_bind_out(long &buffer)
{
    return { .buffer = &buffer, .buffer_type = MYSQL_TYPE_LONG };
}
MYSQL_BIND make_bind_out(long long &buffer)
{
    return { .buffer = &buffer, .buffer_type = MYSQL_TYPE_LONGLONG };
}
MYSQL_BIND make_bind_out(float &buffer)
{
    return { .buffer = &buffer, .buffer_type = MYSQL_TYPE_FLOAT };
}
MYSQL_BIND make_bind_out(std::string &buffer)
{
    buffer.resize(1024, '\0');

    return { .buffer = buffer.data(), .buffer_length = (u_long)buffer.size(), .buffer_type = MYSQL_TYPE_STRING };
}

MYSQL_BIND make_bind_in(const long long &buffer)
{

    return { .buffer = (void*)&buffer, .buffer_type = MYSQL_TYPE_LONGLONG };
}

MYSQL_BIND make_bind_in(const float &buffer)
{

    return { .buffer = (void*)&buffer, .buffer_type = MYSQL_TYPE_FLOAT };
}

MYSQL_BIND make_bind_in(const std::string &buffer)
{







    return { .buffer = (void*)buffer.c_str(), .buffer_length = (u_long)buffer.size(), .buffer_type = MYSQL_TYPE_STRING };
}


