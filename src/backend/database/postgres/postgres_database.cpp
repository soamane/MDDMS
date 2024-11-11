#include "postgres_database.hpp"

#include <QDebug>
#include <QSqlError>

PostgresDatabase::PostgresDatabase(const DatabaseConfig& config) : m_config(config) {
    m_db = QSqlDatabase::addDatabase("QPSQL");
    if (!m_db.isValid()) {
        qDebug() << "Не удалось иницилазировать драйвер PostgreSQL";
        return;
    }
}

PostgresDatabase::~PostgresDatabase() {
    close();
}

bool PostgresDatabase::open() {
    // Установка данных со структуры конфигурации БД
    m_db.setHostName(m_config.getHost());
    m_db.setDatabaseName(m_config.getName());
    m_db.setUserName(m_config.getUser());
    m_db.setPassword(m_config.getPassword());

    if (!m_db.open()) {
        qDebug() << "Ошибка при открытии базы данных: " << m_db.lastError().text();
        return false;
    }

    qDebug() << "Подключение к базе данных " << m_config.getName() << " успешно установлено";
    return true;
}

void PostgresDatabase::close() {
    if (m_db.open()) {
        m_db.close();
    }
}
