#ifndef SHIPPED_DRUGS_TAB_HPP
#define SHIPPED_DRUGS_TAB_HPP

#include "../../../backend/table/shippeddrugs/shipped_drugs_requests_table.hpp"
#include "../base/base_tab_entity.hpp"

class ShippedDrugsTab : public BaseTabEntity<ShippedDrugsRequestsTable> {
    Q_OBJECT

public:
    explicit ShippedDrugsTab(QWidget* parent = nullptr);
    void create() override;

private slots:
    void addRequest();
    void updateRequest();
    void deleteRequest();

private:
    void updateCurrentTab() override;

private:
    QLineEdit* m_patientNameEdit;
    QLineEdit* m_batchIdEdit;
    QLineEdit* m_requestDateEdit;

    QPushButton* m_addButton;
    QPushButton* m_updateButton;
    QPushButton* m_deleteButton;
};

#endif // SHIPPED_DRUGS_TAB_HPP
