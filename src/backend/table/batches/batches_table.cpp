#include "batches_table.hpp"

#include <QDebug>

bool BatchesTable::deleteData(const QStringList& values) {
    if (values.size() != 1) {
        qDebug() << "Неверное количество входных данных для удаления записи";
        return false;
    }

    QString queryStr = "DELETE FROM batches WHERE batch_id = ?";
    return executeQuery(queryStr, values).has_value();
}

bool BatchesTable::entryData(const QStringList& values) {
    if (values.size() != 3) {
        qDebug() << "Неверное количество входных данных для добавления записи";
        return false;
    }

    QString queryStr = "INSERT INTO batches (drug_id, supplier_id, sale_price) VALUES (?, ?, ?)";
    return executeQuery(queryStr, values).has_value();
}

bool BatchesTable::updateData(const QStringList& values) {
    if (values.size() != 4) {
        qDebug() << "Неверное количество входных данных для обновления записи";
        return false;
    }

    QString queryStr = "UPDATE batches SET drug_id = ?, supplier_id = ?, sale_price = ? WHERE batch_id = ?";
    return executeQuery(queryStr, values).has_value();
}

QSqlQuery BatchesTable::fetchAllData() {
    QString queryStr = "SELECT * FROM batches";
    return executeQuery(queryStr, { }).value();
}
