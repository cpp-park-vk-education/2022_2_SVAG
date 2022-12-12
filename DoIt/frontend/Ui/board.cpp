#include "board.h"


Board::Board(QString _name) :
    name(_name),
    columns(0),
    users(0),
    history(0)
{

}


Board::Board(QString _name, QVector<Column> _columns) :
    name(_name),
    columns(_columns),
    users(0),
    history(0)
{

}


Board::Board(QString _name, QVector<Column> _columns, QVector<User> _users) :
    name(_name),
    columns(_columns),
    users(_users),
    history(0)
{

}


void Board::SetText(const QString& _name) {
    name = _name;
}


QString Board::GetText() const {
    return name;
}


void Board::addColumn(Column _column) {
    columns.append(_column);
}


void Board::deleteColumn(Column _column) {
    columns.removeOne(_column);
}


void Board::swapColumns(int first, int second) {
    qSwap(columns.begin()[first], columns.begin()[second]);
}


QVector<Column> Board::getColumns() {
    return columns;
}


void Board::setUsers(QVector<User> _users) {
    users.append(_users);
}


QVector<User> Board::getUsers() const {
    return users;
}


void Board::addToHistory(Update _update) {
    history.append(_update);
}


QVector<Update> Board::getHistory() const {
    return history;
}


void Board::setBoardNum(int _boardNum) {
    boardNum = _boardNum;
}


int Board::getBoardNum() const {
    return boardNum;
}


int Board::columnCount() const {
    return columns.size();
}


bool operator==(const Board& l, const Board& r) {
    if (l.GetText() == r.GetText())
        return true;

    return false;
}


void Board::Draw() const {

}



BoardManager::BoardManager(QVector<Board> _boards) : boards(_boards) {

}


void BoardManager::addBoard(Board _board) {
    boards.append(_board);
}


void BoardManager::deleteBoard(Board _board) {
    boards.removeOne(_board);
}


QVector<Board> BoardManager::getBoards() const {
    return boards;
}


Board BoardManager::getBoard(int _boardNum) const {
    foreach (Board board, boards) {
        if (board.getBoardNum() == _boardNum)
            return board;
    }

    return Board("");
}
