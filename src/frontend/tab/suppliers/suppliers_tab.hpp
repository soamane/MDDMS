#ifndef SUPPLIERS_TAB_HPP
#define SUPPLIERS_TAB_HPP

#include "../../../backend/table/suppliers/suppliers_table.hpp"
#include "../base/base_tab_entity.hpp"

class SuppliersTab : public BaseTabEntity<SuppliersTable> {
    Q_OBJECT

public:
    explicit SuppliersTab(QWidget* parent = nullptr);
    void create() override;

private slots:
    void addSupplier();
    void updateSupplier();
    void deleteSupplier();

private:
    void updateCurrentTab() override;

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_innEdit;
    QLineEdit* m_addressEdit;
    QPushButton* m_addButton;
    QPushButton* m_updateButton;
    QPushButton* m_deleteButton;
};

#endif // SUPPLIERS_TAB_HPP