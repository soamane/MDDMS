#ifndef SHIPPED_DRUGS_REPORT_TAB_HPP
#define SHIPPED_DRUGS_REPORT_TAB_HPP

#include "../../../backend/table/shippeddrugs/shipped_drugs_requests_table.hpp"
#include "../base/base_tab_entity.hpp"

class ShippedDrugsReportTab : public BaseTabEntity<ShippedDrugsRequestsTable> {
    Q_OBJECT

public:
    explicit ShippedDrugsReportTab(QWidget* parent = nullptr);
    void create() override;

private slots:
    void generateReport();

private:
    void updateCurrentTab() override;

private:
    QLineEdit* m_startDateEdit;
    QLineEdit* m_endDateEdit;
    QPushButton* m_generateButton;
    QLabel* m_totalRevenueLabel;
};

#endif // SHIPPED_DRUGS_REPORT_TAB_HPP
