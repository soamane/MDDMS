#ifndef DRUGS_TABLE_HPP
#define DRUGS_TABLE_HPP

#include "../base/base_table_entity.hpp"

class DrugsTable : public BaseTableEntity {
public:
    DrugsTable() = default;
    ~DrugsTable() = default;

    bool deleteData(const QStringList& values) override;
    bool entryData(const QStringList& values) override;
    bool updateData(const QStringList& values) override;
    QSqlQuery fetchAllData() override;
};

#endif // DRUGS_TABLE_HPP