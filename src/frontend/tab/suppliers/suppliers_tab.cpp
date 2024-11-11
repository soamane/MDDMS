#include "suppliers_tab.hpp"
#include "suppliers_tab.moc"

#include <QHeaderView>
#include <QMessageBox>

SuppliersTab::SuppliersTab(QWidget* parent)
    : BaseTabEntity<SuppliersTable>(parent),
    m_nameEdit(new QLineEdit()),
    m_innEdit(new QLineEdit()),
    m_addressEdit(new QLineEdit()),
    m_addButton(new QPushButton("Добавить")),
    m_updateButton(new QPushButton("Обновить")),
    m_deleteButton(new QPushButton("Удалить")) {

    setLayout(m_layout);
    m_layout->addWidget(m_tableWidget);
    m_layout->addWidget(m_nameEdit);
    m_layout->addWidget(m_innEdit);
    m_layout->addWidget(m_addressEdit);
    m_layout->addWidget(m_addButton);
    m_layout->addWidget(m_updateButton);
    m_layout->addWidget(m_deleteButton);

    create();

    connect(m_addButton, &QPushButton::clicked, this, &SuppliersTab::addSupplier);
    connect(m_updateButton, &QPushButton::clicked, this, &SuppliersTab::updateSupplier);
    connect(m_deleteButton, &QPushButton::clicked, this, &SuppliersTab::deleteSupplier);
    connect(m_tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]()
    {
        updateButtonState({ m_addButton, m_updateButton, m_deleteButton });
    });
}

void SuppliersTab::create() {
    QSqlQuery query = m_table.fetchAllData();

    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(4);
    m_tableWidget->setHorizontalHeaderLabels({ "Уникальный номер", "Название", "ИНН", "Адрес" });

    int row = 0;
    while (query.next()) {
        m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        m_tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ++row;
    }

    m_tableWidget->resizeColumnsToContents();
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < m_tableWidget->columnCount(); ++i) {
        m_tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    m_nameEdit->setPlaceholderText("Название");
    m_innEdit->setPlaceholderText("ИНН");
    m_addressEdit->setPlaceholderText("Адрес");

    updateButtonState({ m_addButton, m_updateButton, m_deleteButton });
}

void SuppliersTab::addSupplier() {
    QString name = m_nameEdit->text();
    QString inn = m_innEdit->text();
    QString address = m_addressEdit->text();

    if (name.isEmpty() || inn.isEmpty() || address.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    if (!m_table.entryData({ name, inn, address })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить поставщика в базу данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void SuppliersTab::updateSupplier() {
    int row = m_tableWidget->currentRow();

    QString name = m_nameEdit->text();
    QString inn = m_innEdit->text();
    QString address = m_addressEdit->text();

    if (name.isEmpty() || address.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.updateData({ name, inn, address, id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить запись в базе данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void SuppliersTab::deleteSupplier() {
    int row = m_tableWidget->currentRow();
    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.deleteData({ id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить поставщика из базы данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void SuppliersTab::updateCurrentTab() {
    create();
    clearInputFields({ m_innEdit, m_nameEdit, m_addressEdit });
}
