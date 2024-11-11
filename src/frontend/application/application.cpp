#include "application.moc"
#include "application.hpp"

#include "../tab/drugs/drugs_tab.hpp"
#include "../tab/diseases/diseases_tab.hpp"
#include "../tab/diseasesdrugs/diseases_drugs_tab.hpp"
#include "../tab/suppliers/suppliers_tab.hpp"
#include "../tab/batches/batches_tab.hpp"
#include "../tab/shippeddrugs/shipped_drugs_tab.hpp"
#include "../tab/shippeddrugsreport/shipped_drugs_report_tab.hpp"

#include <QTabWidget>
#include <QWidget>

MainWindow::MainWindow() {
    setFixedSize(1000, 600);
    setWindowTitle("Система управления базой медицинских препаратов (СУБМП)");

    RegisterWidgetTabs();
}

void MainWindow::RegisterWidgetTabs() {
    QTabWidget* tabWidget = new QTabWidget(this);

    tabWidget->addTab(new DrugsTab(), "Медицинские препараты");
    tabWidget->addTab(new DiseasesTab(), "Заболевания");
    tabWidget->addTab(new DiseasesDrugsTab(), "Назначаемые препараты");
    tabWidget->addTab(new SuppliersTab(), "Поставщики");
    tabWidget->addTab(new BatchesTab(), "Партии препаратов");
    tabWidget->addTab(new ShippedDrugsTab(), "Отгрузки");
    tabWidget->addTab(new ShippedDrugsReportTab(), "Отчёт по отгрузкам");

    setCentralWidget(tabWidget);
}
