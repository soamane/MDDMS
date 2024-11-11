#ifndef BASE_TABLE_ENTITY_HPP
#define BASE_TABLE_ENTITY_HPP

#include <QList>
#include <QSqlQuery>
#include <QSqlError>

#include <optional>

class BaseTableEntity {
public:
    BaseTableEntity() = default;
    virtual ~BaseTableEntity() { };

    virtual bool deleteData(const QStringList& values) = 0;
    virtual bool entryData(const QStringList& values) = 0;
    virtual bool updateData(const QStringList& values) = 0;
    virtual QSqlQuery fetchAllData() = 0;

protected:
    std::optional<QSqlQuery> executeQuery(const QString& qstr, const QStringList& bindValues);
};

#endif // BASE_TABLE_ENTITY_HPP