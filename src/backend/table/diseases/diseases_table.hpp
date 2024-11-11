#ifndef DISEASES_TABLE_HPP
#define DISEASES_TABLE_HPP

#include "../base/base_table_entity.hpp"

class DiseasesTable : public BaseTableEntity {
public:
    DiseasesTable() = default;
    ~DiseasesTable() = default;

    bool deleteData(const QStringList& values) override;
    bool entryData(const QStringList& values) override;
    bool updateData(const QStringList& values) override;
    QSqlQuery fetchAllData() override;
};

#endif // DISEASES_TABLE_HPP