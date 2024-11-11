#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

private:
    void RegisterWidgetTabs();
};
