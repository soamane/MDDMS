#ifndef BATCHES_TABLE_HPP
#define BATCHES_TABLE_HPP

#include "../base/base_table_entity.hpp"

class BatchesTable : public BaseTableEntity {
public:
    BatchesTable() = default;
    ~BatchesTable() = default;

    bool deleteData(const QStringList& values) override;
    bool entryData(const QStringList& values) override;
    bool updateData(const QStringList& values) override;
    QSqlQuery fetchAllData() override;
};

#endif // BATCHES_TABLE_HPP
