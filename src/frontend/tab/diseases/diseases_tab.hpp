#ifndef DISEASES_TAB_HPP
#define DISEASES_TAB_HPP

#include "../../../backend/table/diseases/diseases_table.hpp"
#include "../base/base_tab_entity.hpp"

class DiseasesTab : public BaseTabEntity<DiseasesTable> {
    Q_OBJECT

public:
    explicit DiseasesTab(QWidget* parent = nullptr);
    void create() override;

private slots:
    void addDisease();
    void updateDisease();
    void deleteDisease();

private:
    void updateCurrentTab() override;

private:
    QLineEdit* m_nameEdit;
    QLineEdit* m_descriptionEdit;

    QPushButton* m_addButton;
    QPushButton* m_updateButton;
    QPushButton* m_deleteButton;
};

#endif // DISEASES_TAB_HPP