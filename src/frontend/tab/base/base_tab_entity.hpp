#ifndef BASE_TAB_ENTITY_HPP
#define BASE_TAB_ENTITY_HPP

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>

template<typename T>
class BaseTabEntity : public QWidget {
public:
    explicit BaseTabEntity(QWidget* parent = nullptr);
    virtual ~BaseTabEntity() = default;

    virtual void create() = 0;

protected:
    void clearInputFields(const std::vector<QLineEdit*>& lineEdits);
    void updateButtonState(const std::vector<QPushButton*>& pushButtons);

protected:
    virtual void updateCurrentTab() = 0;

protected:
    T m_table;
    QVBoxLayout* m_layout;
    QTableWidget* m_tableWidget;
};

template<typename T>
BaseTabEntity<T>::BaseTabEntity(QWidget* parent) : QWidget(parent), m_layout(new QVBoxLayout()), m_tableWidget(new QTableWidget(this)) { }

template<typename T>
inline void BaseTabEntity<T>::clearInputFields(const std::vector<QLineEdit*>& lineEdits) {
    for (auto& lineEdit : lineEdits) {
        if (lineEdit) {
            lineEdit->clear();
        }
    }
}

template<typename T>
inline void BaseTabEntity<T>::updateButtonState(const std::vector<QPushButton*>& pushButtons) {
    bool hasSelection = m_tableWidget->currentRow() != -1;
    for (auto& button : pushButtons) {
        if (button) {
            button->setEnabled(hasSelection);
        }
    }
}

#endif // BASE_TAB_ENTITY_HPP