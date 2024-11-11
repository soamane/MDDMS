#ifndef SUPPLIERS_TABLE_HPP
#define SUPPLIERS_TABLE_HPP

#include "../base/base_table_entity.hpp"

class SuppliersTable : public BaseTableEntity {
public:
    SuppliersTable() = default;
    ~SuppliersTable() = default;

    bool deleteData(const QStringList& values) override;
    bool entryData(const QStringList& values) override;
    bool updateData(const QStringList& values) override;
    QSqlQuery fetchAllData() override;
};

#endif // SUPPLIERS_TABLE_HPP
