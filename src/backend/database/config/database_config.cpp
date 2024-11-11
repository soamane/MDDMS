#include "database_config.hpp"

DatabaseConfig::DatabaseConfig(const QString& host, const QString& dbname, const QString& user, const QString& password)
    : host(host), dbname(dbname), user(user), password(password) { }

QString DatabaseConfig::getHost() const {
    return host;
}

QString DatabaseConfig::getName() const {
    return dbname;
}

QString DatabaseConfig::getUser() const {
    return user;
}

QString DatabaseConfig::getPassword() const {
    return password;
}
