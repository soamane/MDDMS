#include "suppliers_table.hpp"

#include <QDebug>

bool SuppliersTable::deleteData(const QStringList& values) {
    if (values.size() != 1) {
        qDebug() << "Неверное количество входных данных для удаления записи";
        return false;
    }

    QString queryStr = "DELETE FROM suppliers WHERE supplier_id = ?";
    return executeQuery(queryStr, values).has_value();
}

bool SuppliersTable::entryData(const QStringList& values) {
    if (values.size() != 3) {
        qDebug() << "Неверное количество входных данных для добавления записи";
        return false;
    }

    QString queryStr = "INSERT INTO suppliers (supplier_name, supplier_inn, supplier_address) "
        "VALUES (?, ?, ?)";
    return executeQuery(queryStr, values).has_value();
}

bool SuppliersTable::updateData(const QStringList& values) {
    if (values.size() != 4) {
        qDebug() << "Неверное количество входных данных для обновления записи";
        return false;
    }

    QString queryStr = "UPDATE suppliers SET supplier_name = ?, supplier_inn = ?, supplier_address = ? "
        "WHERE supplier_id = ?";
    return executeQuery(queryStr, values).has_value();
}

QSqlQuery SuppliersTable::fetchAllData() {
    QString queryStr = "SELECT * FROM suppliers";
    return executeQuery(queryStr, { }).value();
}
