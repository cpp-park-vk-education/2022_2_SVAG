#include <gtest/gtest.h>

#include "mainwindow.h"

// Cards //

TEST(TestCard, SettersAndGetters) {
    Card card("Title", "Caption", QDateTime(QDate(2022, 12, 11), QTime(8, 0)));
}