#include "shipped_drugs_report_tab.hpp"
#include "shipped_drugs_report_tab.moc"

#include <QHeaderView>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>

#include <QDebug>

ShippedDrugsReportTab::ShippedDrugsReportTab(QWidget* parent)
    : BaseTabEntity<ShippedDrugsRequestsTable>(parent),
    m_startDateEdit(new QLineEdit()),
    m_endDateEdit(new QLineEdit()),
    m_generateButton(new QPushButton("Генерировать отчет")),
    m_totalRevenueLabel(new QLabel("Итоговая выручка: 0")) {

    setLayout(m_layout);
    m_layout->addWidget(m_startDateEdit);
    m_layout->addWidget(m_endDateEdit);
    m_layout->addWidget(m_generateButton);
    m_layout->addWidget(m_tableWidget);
    m_layout->addWidget(m_totalRevenueLabel);

    create();

    connect(m_generateButton, &QPushButton::clicked, this, &ShippedDrugsReportTab::generateReport);
}

void ShippedDrugsReportTab::create() {
    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({ "Код заявки", "ФИО пациента", "Название препарата", "Цена продажи", "Дата заявки" });

    m_tableWidget->resizeColumnsToContents();
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    m_startDateEdit->setPlaceholderText("Дата начала (например: 2024-01-01)");
    m_endDateEdit->setPlaceholderText("Дата окончания (например: 2024-12-31)");

    for (int i = 0; i < m_tableWidget->columnCount(); ++i) {
        m_tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

void ShippedDrugsReportTab::updateCurrentTab() {
    create();
    clearInputFields({ m_startDateEdit, m_endDateEdit });
}

void ShippedDrugsReportTab::generateReport() {
    QString startDate = m_startDateEdit->text();
    QString endDate = m_endDateEdit->text();

    if (startDate.isEmpty() || endDate.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните оба поля даты");
        return;
    }

    updateCurrentTab();

    QStringList values{ startDate, endDate };
    QSqlQuery query = m_table.generateReportOfData(values);

    double totalRevenue = 0.0;
    int row = 0;

    while (query.next()) {
        m_tableWidget->insertRow(row);
        m_tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        m_tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        m_tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        m_tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        m_tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));

        totalRevenue += query.value(3).toDouble();
        ++row;
    }

    m_totalRevenueLabel->setText(QString("Итоговая выручка: %1").arg(totalRevenue));
}