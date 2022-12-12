#pragma once

#include "column.h"

#include <QVector>

class Board : public IText, IDraw {
public:
    Board() = default;
    Board(QString _name);
    Board(QString _name, QVector<Column> _columns);
    Board(QString _name, QVector<Column> _columns, QVector<User> _users);
    ~Board() = default;

    virtual void SetText(const QString& _name) override;
    virtual QString GetText() const override;

    void addColumn(Column _column);
    void deleteColumn(Column _column);
    void swapColumns(int first, int second);
    QVector<Column> getColumns();

    void setUsers(QVector<User> _users);
    QVector<User> getUsers() const;

    void addToHistory(Update _update);
    QVector<Update> getHistory() const;

    void setBoardNum(int _boardNum);
    int getBoardNum() const;

    int columnCount() const;


    virtual void Draw() const override;

private:
    QString name;
    QVector<Column> columns;
    QVector<User> users;
    QVector<Update> history;
    // image

    int boardNum;
};

class BoardManager {
public:
    BoardManager() = default;
    BoardManager(QVector<Board> _boards);
    ~BoardManager() = default;

    void addBoard(Board _board);
    void deleteBoard(Board _board);
    QVector<Board> getBoards() const;
    Board getBoard(int _boardNum) const;

private:
    QVector<Board> boards;
};

