#include "shipped_drugs_tab.hpp"
#include "shipped_drugs_tab.moc"

#include <QHeaderView>
#include <QMessageBox>

ShippedDrugsTab::ShippedDrugsTab(QWidget* parent)
    : BaseTabEntity<ShippedDrugsRequestsTable>(parent),
    m_patientNameEdit(new QLineEdit()),
    m_batchIdEdit(new QLineEdit()),
    m_requestDateEdit(new QLineEdit()),
    m_addButton(new QPushButton("Добавить")),
    m_updateButton(new QPushButton("Обновить")),
    m_deleteButton(new QPushButton("Удалить")) {

    setLayout(m_layout);
    m_layout->addWidget(m_tableWidget);
    m_layout->addWidget(m_patientNameEdit);
    m_layout->addWidget(m_batchIdEdit);
    m_layout->addWidget(m_requestDateEdit);
    m_layout->addWidget(m_addButton);
    m_layout->addWidget(m_updateButton);
    m_layout->addWidget(m_deleteButton);

    create();

    connect(m_addButton, &QPushButton::clicked, this, &ShippedDrugsTab::addRequest);
    connect(m_updateButton, &QPushButton::clicked, this, &ShippedDrugsTab::updateRequest);
    connect(m_deleteButton, &QPushButton::clicked, this, &ShippedDrugsTab::deleteRequest);
    connect(m_tableWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]()
    {
        updateButtonState({ m_addButton, m_updateButton, m_deleteButton });
    });
}

void ShippedDrugsTab::create() {
    QSqlQuery query = m_table.fetchAllData();

    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(4);
    m_tableWidget->setHorizontalHeaderLabels({ "Код заявки", "ФИО пациента", "Код партии", "Дата заявки" });

    int row = 0;
    while (query.next()) {
        m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));  // request_id
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));  // patient_name
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));  // batch_id
        m_tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));  // request_date
        ++row;
    }

    m_tableWidget->resizeColumnsToContents();
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    for (int i = 0; i < m_tableWidget->columnCount(); ++i) {
        m_tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    m_patientNameEdit->setPlaceholderText("ФИО пациента");
    m_batchIdEdit->setPlaceholderText("Код партии");
    m_requestDateEdit->setPlaceholderText("Дата заявки");

    updateButtonState({ m_addButton, m_updateButton, m_deleteButton });
}

void ShippedDrugsTab::addRequest() {
    QString patientName = m_patientNameEdit->text();
    QString batchId = m_batchIdEdit->text();
    QString requestDate = m_requestDateEdit->text();

    if (patientName.isEmpty() || batchId.isEmpty() || requestDate.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    if (!m_table.entryData({ patientName, batchId, requestDate })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить заявку в базу данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void ShippedDrugsTab::updateRequest() {
    int row = m_tableWidget->currentRow();

    QString patientName = m_patientNameEdit->text();
    QString batchId = m_batchIdEdit->text();
    QString requestDate = m_requestDateEdit->text();

    if (patientName.isEmpty() || batchId.isEmpty() || requestDate.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля и повторите попытку");
        return;
    }

    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.updateData({ patientName, batchId, requestDate, id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить запись в базе данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void ShippedDrugsTab::deleteRequest() {
    int row = m_tableWidget->currentRow();
    QString id = m_tableWidget->item(row, 0)->text();
    if (!m_table.deleteData({ id })) {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить заявку из базы данных. Попробуйте повторить попытку");
        return;
    }

    updateCurrentTab();
}

void ShippedDrugsTab::updateCurrentTab() {
    create();
    clearInputFields({ m_patientNameEdit, m_batchIdEdit, m_requestDateEdit });
}
