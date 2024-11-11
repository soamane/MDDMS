#include "shipped_drugs_requests_table.hpp"

#include <QDate>
#include <QDebug>

bool ShippedDrugsRequestsTable::deleteData(const QStringList& values) {
    if (values.size() != 1) {
        qDebug() << "Неверное количество входных данных для удаления записи";
        return false;
    }

    QString queryStr = "DELETE FROM shipped_drugs_requests WHERE request_id = ?";
    return executeQuery(queryStr, values).has_value();
}

bool ShippedDrugsRequestsTable::entryData(const QStringList& values) {
    if (values.size() != 3) {
        qDebug() << "Неверное количество входных данных для добавления записи";
        return false;
    }

    QString queryStr = "INSERT INTO shipped_drugs_requests (patient_name, batch_id, request_date) VALUES (?, ?, ?)";
    return executeQuery(queryStr, values).has_value();
}

bool ShippedDrugsRequestsTable::updateData(const QStringList& values) {
    if (values.size() != 4) {
        qDebug() << "Неверное количество входных данных для обновления записи";
        return false;
    }

    QString queryStr = "UPDATE shipped_drugs_requests SET patient_name = ?, batch_id = ?, request_date = ? WHERE request_id = ?";
    return executeQuery(queryStr, values).has_value();
}

QSqlQuery ShippedDrugsRequestsTable::fetchAllData() {
    QString queryStr = "SELECT * FROM shipped_drugs_requests";
    return executeQuery(queryStr, { }).value();
}

QSqlQuery ShippedDrugsRequestsTable::generateReportOfData(const QStringList& values) {
    if (values.size() != 2) {
        qDebug() << "Неверное количество входных данных для генерации отчета";
        return QSqlQuery();
    }

    // Подготовленный запрос с параметрами
    QString queryStr = "SELECT shipped_drugs_requests.request_id, "
        "shipped_drugs_requests.patient_name, "
        "drugs.drug_name, "
        "batches.sale_price, "
        "shipped_drugs_requests.request_date "
        "FROM shipped_drugs_requests "
        "JOIN batches ON shipped_drugs_requests.batch_id = batches.batch_id "
        "JOIN drugs ON batches.drug_id = drugs.drug_id "
        "WHERE shipped_drugs_requests.request_date BETWEEN ? AND ?";

    QSqlQuery query;
    query.prepare(queryStr);

    // Привязка значений параметров
    query.addBindValue(values.at(0));  // startDate
    query.addBindValue(values.at(1));  // endDate

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return QSqlQuery();  // Возвращаем пустой запрос в случае ошибки
    }

    return query;
}
