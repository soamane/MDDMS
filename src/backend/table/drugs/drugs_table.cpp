#include "drugs_table.hpp"

#include <QDebug>

bool DrugsTable::deleteData(const QStringList& values) {
    if (values.size() != 1) {
        qDebug() << "Неверное количество входных данных для удаления записи";
        return false;
    }

    QString queryStr = "DELETE FROM drugs WHERE drug_id = ?";
    return executeQuery(queryStr, values).has_value();
}

bool DrugsTable::entryData(const QStringList& values) {
    if (values.size() != 2) {
        qDebug() << "Неверное количество входных данных для добавления записи";
        return false;
    }

    QString queryStr = "INSERT INTO drugs (drug_name, drug_description) VALUES (?, ?)";
    return executeQuery(queryStr, values).has_value();
}

bool DrugsTable::updateData(const QStringList& values) {
    if (values.size() != 3) {
        qDebug() << "Неверное количество входных данных для обновления записи";
        return false;
    }

    QString queryStr = "UPDATE drugs SET drug_name = ?, drug_description = ? WHERE drug_id = ?";
    return executeQuery(queryStr, values).has_value();
}

QSqlQuery DrugsTable::fetchAllData() {
    QString queryStr = "SELECT * FROM drugs";
    return executeQuery(queryStr, { }).value();
}
