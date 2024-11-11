#include "base_table_entity.hpp"

#include <QDebug>

std::optional<QSqlQuery> BaseTableEntity::executeQuery(const QString& qstr, const QStringList& bindValues) {
    QSqlQuery query;
    if (!query.prepare(qstr)) {
        qDebug() << "Ошибка обработки запроса: " << query.lastError().text();
        return std::nullopt;
    }

    foreach(const QString & value, bindValues) {
        query.addBindValue(value);
    }

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса: " << query.lastError().text();
        return std::nullopt;
    }

    qDebug() << "Запрос успешно выполнен: " << qstr;

    return std::make_optional(query);
}
