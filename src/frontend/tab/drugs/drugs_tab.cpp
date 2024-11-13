#include "drugs_tab.hpp"
#include "drugs_tab.moc"

#include <QHeaderView>
#include <QMessageBox>

DrugsTab::DrugsTab(QWidget* parent)
    : BaseTabEntity<DrugsTable>(parent),
    m_nameEdit(new QLineEdit()),
    m_descriptionEdit(new QLineEdit()),
    m_addButton(new QPushButton("Добавить")),
    m_updateButton(new QPushButton("Обновить")),
    m_deleteButton(new QPushButton("Удалить")) {

    setLayout(m_layout);
    m_layout->addWidget(m_tableWidget);
    m_layout->addWidget(m_nameEdit);
    m_layout->addWidget(m_descriptionEdit);
    m_layout->addWidget(m_addButton);
    m_layout->addWidget(m_updateButton);
    m_layout->addWidget(m_deleteButton);

    create();

    connect(m_addButton, &QPushButton::clicked, this, &DrugsTab::addDrug);
    connect(m_updateButton, &QPushButton::clicked, this, &DrugsTab::updateDrug);
    connect(m_deleteButton, &QPushButton::clicked, this, &DrugsTab::deleteDrug);
    connect(m_tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]()
    {
        updateButtonState({ m_updateButton, m_deleteButton });
    });
}

void DrugsTab::create() {
    QSqlQuery query = m_table.fetchAllData();

    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels({ "Уникальный номер", "Название", "Описание" });

    int row = 0;
    while (query.next()) {
        m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ++row;
    }

    m_tableWidget->resizeColumnsToContents();
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < m_tableWidget->columnCount(); ++i) {
        m_tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    m_nameEdit->setPlaceholderText("Название препарата");
    m_descriptionEdit->setPlaceholderText("Описание препарата");

    updateButtonState({ m_updateButton, m_deleteButton });
}

void DrugsTab::addDrug() {
    QString name = m_nameEdit->text();
    QString description = m_descriptionEdit->text();

    if (name.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    if (!m_table.entryData({ name, description })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить препарат в базу данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void DrugsTab::updateDrug() {
    int row = m_tableWidget->currentRow();

    QString name = m_nameEdit->text();
    QString description = m_descriptionEdit->text();

    if (name.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.updateData({ name, description, id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить запись в базе данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void DrugsTab::deleteDrug() {
    int row = m_tableWidget->currentRow();
    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.deleteData({ id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить препарат из базы данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void DrugsTab::updateCurrentTab() {
    create();
    clearInputFields({ m_nameEdit, m_descriptionEdit });
}
