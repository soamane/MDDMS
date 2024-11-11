#ifndef DRUGS_TAB_HPP
#define DRUGS_TAB_HPP

#include "../../../backend/table/drugs/drugs_table.hpp"
#include "../base/base_tab_entity.hpp"

class DrugsTab : public BaseTabEntity<DrugsTable> {
    Q_OBJECT

public:
    explicit DrugsTab(QWidget* parent = nullptr);
    void create() override;

private slots:
    void addDrug();
    void updateDrug();
    void deleteDrug();

private:
    void updateCurrentTab() override;

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_descriptionEdit;

    QPushButton* m_addButton;
    QPushButton* m_updateButton;
    QPushButton* m_deleteButton;
};

#endif // DRUGS_TAB_HPP