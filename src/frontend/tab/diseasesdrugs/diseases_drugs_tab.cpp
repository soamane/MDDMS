#include "diseases_drugs_tab.hpp"
#include "diseases_drugs_tab.moc"

#include <QHeaderView>
#include <QMessageBox>

DiseasesDrugsTab::DiseasesDrugsTab(QWidget* parent)
    : BaseTabEntity(parent),
    m_nameEdit(new QLineEdit()),
    m_descriptionEdit(new QLineEdit()),
    m_addButton(new QPushButton("Добавить")),
    m_deleteButton(new QPushButton("Удалить")) {

    setLayout(m_layout);
    m_layout->addWidget(m_tableWidget);
    m_layout->addWidget(m_nameEdit);
    m_layout->addWidget(m_descriptionEdit);
    m_layout->addWidget(m_addButton);
    m_layout->addWidget(m_deleteButton);

    create();

    connect(m_addButton, &QPushButton::clicked, this, &DiseasesDrugsTab::addDiseaseDrug);
    connect(m_deleteButton, &QPushButton::clicked, this, &DiseasesDrugsTab::deleteDiseaseDrug);
    connect(m_tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]()
    {
        updateButtonState({ m_deleteButton });
    });
}

void DiseasesDrugsTab::create() {
    QSqlQuery query = m_table.fetchAllData();

    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(2);
    m_tableWidget->setHorizontalHeaderLabels({ "Код препарата", "Код болезни" });

    int row = 0;
    while (query.next()) {
        m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ++row;
    }

    m_tableWidget->resizeColumnsToContents();
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < m_tableWidget->columnCount(); ++i) {
        m_tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    m_nameEdit->setPlaceholderText("Код препарата");
    m_descriptionEdit->setPlaceholderText("Код болезни");

    updateButtonState({ m_deleteButton });
}

void DiseasesDrugsTab::addDiseaseDrug() {
    QString drugId = m_nameEdit->text();
    QString diseaseId = m_descriptionEdit->text();

    if (drugId.isEmpty() || diseaseId.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    if (!m_table.entryData({ drugId, diseaseId })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить пару в базу данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void DiseasesDrugsTab::deleteDiseaseDrug() {
    int row = m_tableWidget->currentRow();
    QString drugId = m_tableWidget->item(row, 0)->text();
    QString diseaseId = m_tableWidget->item(row, 1)->text();

    if (!m_table.deleteData({ drugId, diseaseId })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить пару из базы данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void DiseasesDrugsTab::updateCurrentTab() {
    create();
    clearInputFields({ m_nameEdit, m_descriptionEdit });
}
