#ifndef DISEASES_DRUGS_TAB_HPP
#define DISEASES_DRUGS_TAB_HPP

#include "../../../backend/table/diseasesdrugs/diseases_drugs_table.hpp"
#include "../base/base_tab_entity.hpp"

class DiseasesDrugsTab : public BaseTabEntity<DiseaseDrugsTable> {
    Q_OBJECT

public:
    explicit DiseasesDrugsTab(QWidget* parent = nullptr);
    void create() override;

private slots:
    void addDiseaseDrug();
    void deleteDiseaseDrug();

private:
    void updateCurrentTab() override;

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_descriptionEdit;

    QPushButton* m_addButton;
    QPushButton* m_deleteButton;
};

#endif // DISEASES_DRUGS_TAB_HPP