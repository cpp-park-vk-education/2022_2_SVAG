#pragma once

#include "ui_mainwindow.h"

#include "object.h"
#include "user.h"
#include "board.h"

#include <QMainWindow>
#include <QDebug>
#include <QPushButton>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

signals:

    // user
    void authUserSignal(User &);

    void registerUserSignal(User &);

    void addUserSignal(User &, const size_t board_id);

    void logoutSignal();

    // object
    void addObjectSignal(Object &, ObjType);

    void delObjectSignal(size_t, ObjType);

    void updateObjectSignal(Object &, ObjType);

public slots:

    void addBoardSlot() {
        // пользователь ввел имя доски и путь до файла c изображением для фона доски
        Board board("Доска 1", "test_640_480.jpg");
        emit addObjectSignal(board, BOARD);
    }

    void addColumnSlot() {
        // пользователь ввел имя колонки
        Column column("Колонка 1", 0);
        emit addObjectSignal(column, COLUMN);
    }

    void addCardSlot() {
        // пользователь ввел данные новой карточки
        Card card("Карточка 1", "Описание карточки 1", 123);
        emit addObjectSignal(card, CARD);
    }

    void addTagSlot() {
        // пользователь ввел данные нового тэга
        Tag tag("Тэг 1", "Красный", 122);
        emit addObjectSignal(tag, TAG);
    }

    void addCheckListSlot() {
        // пользователь ввел данные нового чеклиста
        CheckList checkList("Чек Лист 1", 12);
        emit addObjectSignal(checkList, CHECK_LIST);
    }

    void addCheckListItemSlot() {
        // пользователь ввел данные нового элемента чеклиста
        CheckListItem checkListItem("Чеклист 1", true, 14);
        emit addObjectSignal(checkListItem, CHECK_LIST_ITEM);
    }

    // del object slots
    void delBoardSlot() {
        // пользователь выбрал доску для удаления
        size_t id_board_to_del = 13;
        emit delObjectSignal(id_board_to_del, BOARD);
    }

    void delColumnSlot() {
        // пользователь выбрал колонку для удаления
        size_t id_col_to_del = 13;
        emit delObjectSignal(id_col_to_del, COLUMN);
    }

    void delCardSlot() {
        // пользователь выбрал карточку для удаления
        size_t id_card_to_del = 13;
        emit delObjectSignal(id_card_to_del, CARD);
    }

    void delTagSlot() {
        // пользователь выбрал тэг для удаления
        size_t id_tag_to_del = 13;
        emit delObjectSignal(id_tag_to_del, TAG);
    }

    void delCheckListSlot() {
        // пользователь выбрал чеклист для удаления
        size_t id_check_list_to_del = 13;
        emit delObjectSignal(id_check_list_to_del, CHECK_LIST);
    }

    void delCheckListItemSlot() {
        // пользователь выбрал элемент чеклиста для удаления
        size_t id_check_list_item_to_del = 13;
        emit delObjectSignal(id_check_list_item_to_del, CHECK_LIST_ITEM);
    }

    // update object slots
    void updateBoardSlot() {
        Board board("Доска 1", "test_640_480.jpg");
        emit updateObjectSignal(board, BOARD);
    }

    void updateColumnSlot() {
        Column column("Колонка 1", 0);
        emit updateObjectSignal(column, COLUMN);
    }

    void updateCardSlot() {
        Card card("Карточка 1", "Описание карточки 1", 123);
        emit updateObjectSignal(card, CARD);
    }

    void updateTagSlot() {
        Tag tag("Тэг 1", "Красный", 122);
        emit updateObjectSignal(tag, TAG);
    }

    void updateCheckListSlot() {
        CheckList checkList("Чек Лист 1", 12);
        emit updateObjectSignal(checkList, CHECK_LIST);
    }

    void updateCheckListItemSlot() {
        CheckListItem checkListItem("Чеклист 1", true, 14);
        emit updateObjectSignal(checkListItem, CHECK_LIST_ITEM);
    }

    void addUserSlot() {
        User user("Login 1");
        addUserSignal(user, 23);
    }

    void logoutSlot() {
        emit logoutSignal();
    }

    void authSlot() {
        // пользователь ввел логин, пароль
        User user("Пользователь 1", "password_1");
        emit authUserSignal(user);
    }

    void registerSlot() {
        User user("Пользователь 1", "password_1", "email_1@yandex.ru", "avatar_1.jpg");
        emit registerUserSignal(user);
    }


private:
    Ui::MainWindow *_ui;
};
