#include "batches_tab.hpp"
#include "batches_tab.moc"

#include <QHeaderView>
#include <QMessageBox>

BatchesTab::BatchesTab(QWidget* parent)
    : BaseTabEntity<BatchesTable>(parent),
    m_drugEdit(new QLineEdit()),
    m_supplierEdit(new QLineEdit()),
    m_salePriceEdit(new QLineEdit()),
    m_addButton(new QPushButton("Добавить")),
    m_updateButton(new QPushButton("Обновить")),
    m_deleteButton(new QPushButton("Удалить")) {

    setLayout(m_layout);
    m_layout->addWidget(m_tableWidget);
    m_layout->addWidget(m_drugEdit);
    m_layout->addWidget(m_supplierEdit);
    m_layout->addWidget(m_salePriceEdit);
    m_layout->addWidget(m_addButton);
    m_layout->addWidget(m_updateButton);
    m_layout->addWidget(m_deleteButton);

    create();

    connect(m_addButton, &QPushButton::clicked, this, &BatchesTab::addBatch);
    connect(m_updateButton, &QPushButton::clicked, this, &BatchesTab::updateBatch);
    connect(m_deleteButton, &QPushButton::clicked, this, &BatchesTab::deleteBatch);
    connect(m_tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]()
    {
        updateButtonState({ m_addButton, m_updateButton, m_deleteButton });
    });
}

void BatchesTab::create() {
    QSqlQuery query = m_table.fetchAllData();

    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(4);
    m_tableWidget->setHorizontalHeaderLabels({ "Код партии", "Код препарата", "Код поставщика", "Цена продажи" });

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

    m_drugEdit->setPlaceholderText("Код препарата");
    m_supplierEdit->setPlaceholderText("Код поставщика");
    m_salePriceEdit->setPlaceholderText("Цена продажи");

    clearInputFields({ m_drugEdit, m_supplierEdit, m_salePriceEdit });
}

void BatchesTab::addBatch() {
    QString drug_id = m_drugEdit->text();
    QString supplier_id = m_supplierEdit->text();
    QString sale_price = m_salePriceEdit->text();

    if (drug_id.isEmpty() || sale_price.isEmpty() || supplier_id.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    if (!m_table.entryData({ drug_id, supplier_id, sale_price })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить партию в базу данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void BatchesTab::updateBatch() {
    int row = m_tableWidget->currentRow();

    QString drug_id = m_drugEdit->text();
    QString supplier_id = m_supplierEdit->text();
    QString sale_price = m_salePriceEdit->text();

    if (drug_id.isEmpty() || sale_price.isEmpty() || supplier_id.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.updateData({ drug_id, supplier_id, sale_price, id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить запись в базе данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void BatchesTab::deleteBatch() {
    int row = m_tableWidget->currentRow();
    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.deleteData({ id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить партию из базы данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void BatchesTab::updateCurrentTab() {
    create();
    clearInputFields({ m_drugEdit, m_supplierEdit, m_salePriceEdit });
}
