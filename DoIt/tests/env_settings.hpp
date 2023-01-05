#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "BoardDataBase.h"
#include "CardDataBase.h"
#include "PostgreDataBase.h"
#include "UserDataBase.h"

class TestEnvironment : public ::testing::Environment {
 public:
    static std::shared_ptr<PostgreDataBase> getPgClient() {
        static std::shared_ptr<PostgreConnectParams> conParams =
            std::make_shared<PostgreConnectParams>("db_test", "postgres");

        static std::shared_ptr<PostgreDataBase> pg = std::make_shared<PostgreDataBase>(conParams);

        return pg;
    }

    static UserDataBase getUsersClient() {
        static std::shared_ptr<DataBase> pg = getPgClient();
        static UserDataBase cl(pg);
        return cl;
    }

    static BoardDataBase getBoardClient() {
        static std::shared_ptr<DataBase> pg = getPgClient();
        static BoardDataBase cl(pg);
        return cl;
    }

    static CardDataBase getCardsClient() {
        static std::shared_ptr<DataBase> pg = getPgClient();
        static CardDataBase cl(pg);
        return cl;
    }

    static json getTestDataUsers() {
        std::ifstream input("../../tests/data/users_data.json");
        json users;
        input >> users;

        return users;
    }

    static json getTestDataBoards() {
        std::ifstream input("../../tests/data/boards_data.json");
        json boards;
        input >> boards;

        return boards;
    }

    static json getTestDataCards() {
        std::ifstream input("../../tests/data/cards_data.json");
        json cards;
        input >> cards;

        return cards;
    }

    static json getTestDataColumns() {
        std::ifstream input("../../tests/data/columns_data.json");
        json columns;
        input >> columns;

        return columns;
    }

    static json getTestDataTags() {
        std::ifstream input("../../tests/data/tags_data.json");
        json tags;
        input >> tags;

        return tags;
    }

    static json getTestDataCheckLists() {
        std::ifstream input("../../tests/data/check_lists_data.json");
        json check_lists;
        input >> check_lists;

        return check_lists;
    }

    static json getTestDataCheckListsItems() {
        std::ifstream input("../../tests/data/check_lists_items_data.json");
        json check_lists_items;
        input >> check_lists_items;

        return check_lists_items;
    }

    static json getTestDataUser2Boards() {
        std::ifstream input("../../tests/data/users2boards_data.json");
        json users2boards;
        input >> users2boards;

        return users2boards;
    }
};
