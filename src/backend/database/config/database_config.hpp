#ifndef DATABASE_CONFIG_HPP
#define DATABASE_CONFIG_HPP

#include <QString>

struct DatabaseConfig {
    DatabaseConfig() = default;
    explicit DatabaseConfig(const QString& host, const QString& dbname, const QString& user, const QString& password);

    QString getHost() const;
    QString getName() const;
    QString getUser() const;
    QString getPassword() const;

private:
    QString host;         // Хост базы данных
    QString dbname;       // Имя базы данных
    QString user;         // Имя пользователя
    QString password;     // Пароль пользователя
};

#endif // DATABASE_CONFIG_HPP