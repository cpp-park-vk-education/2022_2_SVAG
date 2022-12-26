#pragma once

#include <QDialog>

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "user.h"
#include <QValidator>
#include <iostream>

class AuthWindow : public QDialog {
Q_OBJECT

public slots:

    void authClickedSlot() {
        QLineEdit *username = findChild<QLineEdit *>("userNameEdit");
        QLineEdit *password = findChild<QLineEdit *>("passwordEdit");
        User user;
//        user.username = username->text().toStdString();
//        user.password = password->text().toStdString();

        user.username = "valera";
        user.password = "12345678";

        emit authSignal(user);
    }

    void openRegSlot() {
    }

signals:

    void authSignal(const User &user);

    void openRegSignal();

public:
    explicit AuthWindow(QWidget *parent = nullptr);

    ~AuthWindow();
};
