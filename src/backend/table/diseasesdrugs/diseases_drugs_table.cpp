#include "diseases_drugs_table.hpp"

#include <QDebug>

bool DiseaseDrugsTable::deleteData(const QStringList& values) {
    if (values.size() != 2) {
        qDebug() << "Неверное количество входных данных для удаления записи";
        return false;
    }

    QString queryStr = "DELETE FROM disease_drugs WHERE drug_id = ? AND disease_id = ?";
    return executeQuery(queryStr, values).has_value();
}

bool DiseaseDrugsTable::entryData(const QStringList& values) {
    if (values.size() != 2) {
        qDebug() << "Неверное количество входных данных для добавления записи";
        return false;
    }

    QString queryStr = "INSERT INTO disease_drugs (drug_id, disease_id) VALUES (?, ?)";
    return executeQuery(queryStr, values).has_value();
}

bool DiseaseDrugsTable::updateData(const QStringList& values) {
    // Логика функции обновления не нужна для данного типа таблицы
    return true;
}

QSqlQuery DiseaseDrugsTable::fetchAllData() {
    QString queryStr = "SELECT * FROM disease_drugs";
    return executeQuery(queryStr, { }).value();
}
