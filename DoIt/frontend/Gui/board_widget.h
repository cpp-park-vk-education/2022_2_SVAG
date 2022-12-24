#pragma once

#include "column_widget.h"

class BoardWidget : public IText, IDraw {
public:
  BoardWidget(QString _name);
  BoardWidget(QString _name, QVector<ColumnWidget> _columns);
  BoardWidget(QString _name, QVector<ColumnWidget> _columns,
              QVector<UiUser> _users);
  ~BoardWidget() = default;

  virtual void SetText(const QString &_name) override;
  virtual QString GetText() const override;

  void addColumn(ColumnWidget _column);
  void deleteColumn(ColumnWidget _column);
  void swapColumns(int first, int second);
  QVector<ColumnWidget> getColumns();

  void setUsers(QVector<UiUser> _users);
  QVector<UiUser> getUsers() const;

  void addToHistory(Update _update);
  QVector<Update> getHistory() const;

  int getID() const;
  QString getName() const { return name; }
  void setID(int id) { ID = id; }

  int columnCount() const;

  QWidget *Draw() const override;

private:
  QString name;
  QVector<ColumnWidget> columns;
  QVector<UiUser> users;
  QVector<Update> history;
  // image

  int ID;
};

class BoardManager {
public:
  BoardManager() = default;
  BoardManager(QVector<BoardWidget> _boards);
  ~BoardManager() = default;

  void addBoard(BoardWidget _board);
  void deleteBoard(BoardWidget _board);
  QVector<BoardWidget> getBoards();

  BoardWidget getBoard(int _boardNum);
  BoardWidget first() const;
  void clear();
  bool empty() const;

private:
  QVector<BoardWidget> boards;
};
