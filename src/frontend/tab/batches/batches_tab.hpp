#ifndef BATCHES_TAB_HPP
#define BATCHES_TAB_HPP

#include "../../../backend/table/batches/batches_table.hpp"
#include "../base/base_tab_entity.hpp"

class BatchesTab : public BaseTabEntity<BatchesTable> {
    Q_OBJECT

public:
    explicit BatchesTab(QWidget* parent = nullptr);
    void create() override;

private slots:
    void addBatch();
    void updateBatch();
    void deleteBatch();

private:
    void updateCurrentTab() override;

private:
    QLineEdit* m_drugEdit;
    QLineEdit* m_supplierEdit;
    QLineEdit* m_salePriceEdit;

    QPushButton* m_addButton;
    QPushButton* m_updateButton;
    QPushButton* m_deleteButton;
};


#endif // BATCHES_TAB_HPP