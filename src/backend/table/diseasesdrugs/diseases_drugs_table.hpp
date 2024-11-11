#ifndef DISEASE_DRUGS_TABLE_HPP
#define DISEASE_DRUGS_TABLE_HPP

#include "../base/base_table_entity.hpp"

class DiseaseDrugsTable : public BaseTableEntity {
public:
    DiseaseDrugsTable() = default;
    ~DiseaseDrugsTable() = default;

    bool deleteData(const QStringList& values) override;
    bool entryData(const QStringList& values) override;
    bool updateData(const QStringList& values) override;
    QSqlQuery fetchAllData() override;
};

#endif // DISEASE_DRUGS_TABLE_HPP