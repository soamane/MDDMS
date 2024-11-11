#include "diseases_table.hpp"

#include <QDebug>

bool DiseasesTable::deleteData(const QStringList& values) {
    if (values.size() != 1) {
        qDebug() << "Неверное количество входных данных для удаления записи";
        return false;
    }

    QString queryStr = "DELETE FROM diseases WHERE disease_id = ?";
    return executeQuery(queryStr, values).has_value();
}

bool DiseasesTable::entryData(const QStringList& values) {
    if (values.size() != 2) {
        qDebug() << "Неверное количество входных данных для добавления записи";
        return false;
    }

    QString queryStr = "INSERT INTO diseases (disease_name, disease_description) VALUES (?, ?)";
    return executeQuery(queryStr, values).has_value();
}

bool DiseasesTable::updateData(const QStringList& values) {
    if (values.size() != 3) {
        qDebug() << "Неверное количество входных данных для обновления записи";
        return false;
    }

    QString queryStr = "UPDATE diseases SET disease_name = ?, disease_description = ? WHERE disease_id = ?";
    return executeQuery(queryStr, values).has_value();
}

QSqlQuery DiseasesTable::fetchAllData() {
    QString queryStr = "SELECT * FROM diseases";
    return executeQuery(queryStr, { }).value();
}
