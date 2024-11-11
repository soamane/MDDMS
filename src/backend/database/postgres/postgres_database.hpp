#ifndef POSTGRES_DATABASE_HPP
#define POSTGRES_DATABASE_HPP

#include "../config/database_config.hpp"

#include <QSqlDatabase>

class PostgresDatabase {
public:
    PostgresDatabase(const DatabaseConfig& config);
    ~PostgresDatabase();

    bool open();
    void close();

private:
    QSqlDatabase m_db;
    const DatabaseConfig& m_config; // Конфигурация данных БД
};

#endif // POSTGRES_DATABASE_HPP