#ifndef SHIPPED_DRUGS_REQUESTS_TABLE_HPP
#define SHIPPED_DRUGS_REQUESTS_TABLE_HPP

#include "../base/base_table_entity.hpp"

class ShippedDrugsRequestsTable : public BaseTableEntity {
public:
    ShippedDrugsRequestsTable() = default;
    ~ShippedDrugsRequestsTable() = default;

    bool deleteData(const QStringList& values) override;
    bool entryData(const QStringList& values) override;
    bool updateData(const QStringList& values) override;

    QSqlQuery fetchAllData() override;
    QSqlQuery generateReportOfData(const QStringList& values);
};

#endif // SHIPPED_DRUGS_REQUESTS_TABLE_HPP
