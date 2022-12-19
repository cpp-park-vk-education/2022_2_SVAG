#include <gtest/gtest.h>

#include "mainwindow.h"


TEST(TestCard, SettersAndGetters) {
    // Card with title, caption, deadline //
    Card card("Title Card", "Caption Card", QDateTime(QDate(2022, 12, 11), QTime(8, 0)));

    EXPECT_EQ(card.GetText(), "Title Card");
    EXPECT_EQ(card.getCaption(), "Caption Card");
    EXPECT_EQ(card.getDeadline().toString(), "Sun Dec 11 08:00:00 2022");

    // Card with title, caption, tags, deadline //
    QVector<QString> tags({"Tag 1", "Tag 2"});
    Card cardWithTags("Title CardWithTags", "Caption CardWithTags", tags, 
        QDateTime(QDate(2022, 12, 11), QTime(12, 30)));

    EXPECT_EQ(cardWithTags.GetText(), "Title CardWithTags");
    EXPECT_EQ(cardWithTags.getCaption(), "Caption CardWithTags");
    EXPECT_EQ(cardWithTags.getDeadline().toString(), "Sun Dec 11 12:30:00 2022");

    for (size_t i = 0; i < card.getTags().size(); ++i) {
        EXPECT_EQ(card.getTags()[i], tags[i]);
    }
}


TEST(TestCard, AddAndDeleteComments) {
    Card cardWithComments("Title CardWithComments", "Caption CardWithComments");
    QVector<Comment> comments({
        {"Comment 1", User("User 1"), QDateTime(QDate(2022, 12, 11), QTime(6, 0))},
        {"Comment 2", User("User 2"), QDateTime(QDate(2022, 12, 11), QTime(7, 0))},
        {"Comment 3", User("User 3"), QDateTime(QDate(2022, 12, 11), QTime(8, 0))}
        });

    // Add comments
    foreach (Comment comment, comments) {
        cardWithComments.addComment(comment);
    }

    EXPECT_EQ(cardWithComments.getComments().size(), 3);

    // Delete comment
    cardWithComments.deleteComment(comments[1]);

    EXPECT_NE(cardWithComments.getComments().size(), 3);
    EXPECT_EQ(cardWithComments.getComments().size(), 2);
    EXPECT_TRUE(cardWithComments.getComments()[0] == comments[0]);
    EXPECT_TRUE(cardWithComments.getComments()[1] == comments[2]);
}


TEST(TestColumn, SettersAndGetters) {
    Column column("Name");

    EXPECT_EQ(column.GetText(), "Name");
}


TEST(TestColumn, AddAndDeleteCards) {
    // Cards //
    QVector<Card> cards({
        {"Title Card 1", "Caption Card 1", QDateTime(QDate(2022, 12, 11), QTime(8, 0))},
        {"Title Card 2", "Caption Card 2", QDateTime(QDate(2022, 12, 11), QTime(9, 0))},
        {"Title Card 3", "Caption Card 3", {"Tag 1 Card 3", "Tag 2 Card 3"}, 
            QDateTime(QDate(2022, 12, 11), QTime(10, 0))}
        });

    // Column //
    Column columnWithCards("Column", cards);

    EXPECT_EQ(columnWithCards.cardCount(), 3);

    // Add card
    Card newCard("Title Card 4", "Caption Card 4");
    columnWithCards.addCard(newCard);

    EXPECT_EQ(columnWithCards.cardCount(), 4);

    // Swap cards
    columnWithCards.swapCards(0, 2);

    EXPECT_TRUE(columnWithCards.getCards()[0] == cards[2]);
    EXPECT_TRUE(columnWithCards.getCards()[2] == cards[0]);

    // Delete card
    columnWithCards.deleteCard(newCard);

    EXPECT_EQ(columnWithCards.cardCount(), 3);
}


TEST(TestBoard, SettersAndGetters) {
    // Columns //
    QVector<Column> columns({
        {"Column 1",},
        {"Column 2", {{"Title Card 1", "Caption Card 1", QDateTime(QDate(2022, 12, 11), QTime(8, 0))}}},
        });
    
    // Users //
    QVector<User> users({
        {"User 1"},
        {"User 2"},
        });
    
    // Board //
    Board board("Board", columns, users);

    EXPECT_EQ(board.GetText(), "Board");
    EXPECT_EQ(board.columnCount(), 2);
    EXPECT_EQ(board.getUsers().size(), 2);
}


TEST(TestBoard, AddAndDeleteColumns) {
    // Columns //
    QVector<Column> columns({
        {"Column 1",},
        {"Column 2", {{"Title Card 1", "Caption Card 1"}, {"Title Card 2", "Caption Card 2"}}},
        });
    
    // Users //
    QVector<User> users({
        {"User 1"},
        {"User 2"},
        });
    
    // Board //
    Board board("Board", columns, users);

    EXPECT_EQ(board.columnCount(), 2);

    // Add column
    QVector<Card> cards({
        {"Title Card 1", "Caption Card 1"},
        {"Title Card 2", "Caption Card 2"}
        });
    Column newColumn("Column 3", cards);
    board.addColumn(newColumn);

    EXPECT_EQ(board.columnCount(), 3);

    // Swap columns
    board.swapColumns(1, 2);

    EXPECT_TRUE(board.getColumns()[1] == newColumn);
    EXPECT_TRUE(board.getColumns()[2] == columns[1]);

    // Delete card
    board.deleteColumn(newColumn);

    EXPECT_EQ(board.columnCount(), 2);
    EXPECT_TRUE(board.getColumns()[1] == columns[1]);
}
