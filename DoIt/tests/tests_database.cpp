#include "env_settings.hpp"

/* ============ TEST UserDataBase ================ */

TEST(TestAddUser, newUser) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    json request = {{"username", "aaaaaa"}, {"email", "123@mail.ru"}, {"password", "1234556"}};
    json response = cl.addUser(request);

    json users = TestEnvironment::getTestDataUsers();
    size_t id = users.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["users"][0]["id"], id);
    EXPECT_EQ(response["users"][0]["username"], request["username"]);
    EXPECT_EQ(response["users"][0]["email"], request["email"]);
    EXPECT_EQ(response["users"][0]["password"], request["password"]);
    EXPECT_EQ(response["users"][0]["avatar"], request["avatar"]);
}

TEST(TestAddUser, oldUser) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    json request = {{"username", "aaaaaa"}, {"email", "123@mail.ru"}, {"password", "1234556"}};
    json response = cl.addUser(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveUser, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 1;
    json response = cl.removeUser(id);
    json users = TestEnvironment::getTestDataUsers();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["users"][0]["id"], id);
    EXPECT_EQ(response["users"][0]["username"], users[0]["username"]);
    EXPECT_EQ(response["users"][0]["email"], users[0]["email"]);
    EXPECT_EQ(response["users"][0]["password"], users[0]["password"]);
    EXPECT_EQ(response["users"][0]["avatar"], users[0]["avatar"]);
}

TEST(TestRemoveUser, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json response = cl.removeUser(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestCheckUserExists, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 1;
    bool response = cl.checkUserExists(id);

    EXPECT_EQ(response, true);
}

TEST(TestCheckUserExists, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    bool response = cl.checkUserExists(id);

    EXPECT_EQ(response, false);
}

TEST(TestUpdateUser, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 1;
    json request = {{"id", id}, {"username", "aaaaaa"}, {"email", "123@mail.ru"}, {"password", "1234556"}};
    json response = cl.updateUser(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["users"][0]["id"], id);
    EXPECT_EQ(response["users"][0]["username"], request["username"]);
    EXPECT_EQ(response["users"][0]["email"], request["email"]);
    EXPECT_EQ(response["users"][0]["password"], request["password"]);
    EXPECT_EQ(response["users"][0]["avatar"], request["avatar"]);
}

TEST(TestUpdateUser, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json request = {{"id", id}, {"username", "aaaaaa"}, {"email", "123@mail.ru"}, {"password", "1234556"}};
    json response = cl.updateUser(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetUserInfo, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 1;
    json response = cl.getUserInfo(id);
    json users = TestEnvironment::getTestDataUsers();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["users"][0]["id"], id);
    EXPECT_EQ(response["users"][0]["username"], users[0]["username"]);
    EXPECT_EQ(response["users"][0]["email"], users[0]["email"]);
    EXPECT_EQ(response["users"][0]["password"], users[0]["password"]);
    EXPECT_EQ(response["users"][0]["avatar"], users[0]["avatar"]);
}

TEST(TestGetUserInfo, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json response = cl.getUserInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetUserBoards, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 2;
    json response = cl.getUserBoards(id);

    json boards = TestEnvironment::getTestDataBoards();
    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["boards"][0]["name"], boards["name"]);
    EXPECT_EQ(response["boards"][0]["caption"], boards["caption"]);
}

TEST(TestGetUserBoards, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json response = cl.getUserBoards(id);

    EXPECT_EQ(response["status"], "error");
}

/* ============ TEST BoardDataBase ================ */

TEST(TestAddBoard, newBoard) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    json request = {{"user_id", 3}, {"name", "aaaaaa"}, {"caption", "bbbbbbbb"}};
    json response = cl.addBoard(request);

    json boards = TestEnvironment::getTestDataBoards();
    size_t id = boards.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["boards"][0]["id"], id);
    EXPECT_EQ(response["boards"][0]["name"], request["name"]);
    EXPECT_EQ(response["boards"][0]["caption"], request["caption"]);
}

TEST(TestRemoveBoard, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1;
    json response = cl.removeBoard(id);
    json boards = TestEnvironment::getTestDataBoards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["boards"][0]["id"], id);
    EXPECT_EQ(response["boards"][0]["name"], boards[0]["name"]);
    EXPECT_EQ(response["boards"][0]["caption"], boards[0]["caption"]);
}

TEST(TestRemoveBoard, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.removeBoard(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestUpdateBoard, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1;
    json request = {{"id", id}, {"name", "123a"}, {"caption", "dafkadk"}};
    json response = cl.updateBoard(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["boards"][0]["id"], id);
    EXPECT_EQ(response["boards"][0]["name"], request["name"]);
    EXPECT_EQ(response["boards"][0]["caption"], request["caption"]);
}

TEST(TestUpdateBoard, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json request = {{"id", id}, {"name", "123a"}, {"caption", "dafkadk"}};
    json response = cl.updateBoard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardInfo, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1;
    json response = cl.getBoardInfo(id);
    json boards = TestEnvironment::getTestDataBoards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["boards"][0]["id"], id);
    EXPECT_EQ(response["boards"][0]["name"], boards[0]["name"]);
    EXPECT_EQ(response["boards"][0]["caption"], boards[0]["caption"]);
}

TEST(TestGetBoardInfo, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.getBoardInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardUsers, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1;
    json response = cl.getBoardUsers(id);
    json users = TestEnvironment::getTestDataUsers();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["users"][0]["username"], users[1]["username"]);
    EXPECT_EQ(response["users"][0]["email"], users[1]["email"]);
    EXPECT_EQ(response["users"][0]["password"], users[1]["password"]);
    EXPECT_EQ(response["users"][0]["avatar"], users[1]["avatar"]);
}

TEST(TestGetBoardUsers, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.getBoardUsers(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardColumns, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1;
    json response = cl.getBoardColumns(id);
    json columns = TestEnvironment::getTestDataColumns();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["columns"][0]["name"], columns[0]["name"]);
    EXPECT_EQ(response["columns"][0]["board_id"], columns[0]["board_id"]);
    EXPECT_EQ(response["columns"][1]["name"], columns[2]["name"]);
    EXPECT_EQ(response["columns"][1]["board_id"], columns[2]["board_id"]);
}

TEST(TestGetBoardColumns, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.getBoardUsers(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardColumn, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1, column_id = 1;
    json response = cl.getBoardColumn(id, column_id);
    json columns = TestEnvironment::getTestDataColumns(), cards = TestEnvironment::getTestDataCards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["columns"][0]["name"], columns[0]["name"]);
    EXPECT_EQ(response["columns"][0]["board_id"], columns[0]["board_id"]);
    EXPECT_EQ(response["columns"][0]["cards"][0]["name"], cards[2]["name"]);
    EXPECT_EQ(response["columns"][0]["cards"][0]["caption"], cards[2]["caption"]);
    EXPECT_EQ(response["columns"][0]["cards"][0]["deadline"], cards[2]["deadline"]);
    EXPECT_EQ(response["columns"][0]["cards"][0]["column_id"], cards[2]["column_id"]);
    EXPECT_EQ(response["columns"][0]["cards"][1]["name"], cards[6]["name"]);
    EXPECT_EQ(response["columns"][0]["cards"][1]["caption"], cards[6]["caption"]);
    EXPECT_EQ(response["columns"][0]["cards"][1]["deadline"], cards[6]["deadline"]);
    EXPECT_EQ(response["columns"][0]["cards"][1]["column_id"], cards[6]["column_id"]);
}

TEST(TestGetBoardColumn, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10, column_id = 1;
    json response = cl.getBoardColumn(id, column_id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardColumn, ColumnNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1, column_id = 2;
    json response = cl.getBoardColumn(id, column_id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestAddColumn, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    json request = {{"name", "aaaaaa"}, {"board_id", 1}};
    json response = cl.addColumn(request);

    json columns = TestEnvironment::getTestDataColumns();
    size_t id = columns.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["columns"][0]["id"], id);
    EXPECT_EQ(response["columns"][0]["name"], request["name"]);
    EXPECT_EQ(response["columns"][0]["board_id"], request["board_id"]);
}

TEST(TestAddColumn, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    json request = {{"name", "aaaaaa"}, {"board_id", 11}};
    json response = cl.addColumn(request);

    EXPECT_EQ(response["status"], "error");
}

/* ============ TEST CardDataBase ================ */

TEST(TestAddCard, columnExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    json request = {{"name", "first"}, {"caption", "second"}, {"deadline", nullptr}, {"column_id", 1}};
    json response = cl.addCard(request);

    json cards = TestEnvironment::getTestDataCards();
    size_t id = cards.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["cards"][0]["id"], id);
    EXPECT_EQ(response["cards"][0]["name"], request["name"]);
    EXPECT_EQ(response["cards"][0]["caption"], request["caption"]);
    EXPECT_EQ(response["cards"][0]["deadline"], request["deadline"]);
    EXPECT_EQ(response["cards"][0]["column_id"], request["column_id"]);
}

TEST(TestAddCard, columnNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    json request = {{"name", "first"}, {"caption", "second"}, {"deadline", nullptr}, {"column_id", 1}};
    json response = cl.addCard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveCard, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.removeCard(id);
    json cards = TestEnvironment::getTestDataCards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["cards"][0]["id"], id);
    EXPECT_EQ(response["cards"][0]["name"], cards["name"]);
    EXPECT_EQ(response["cards"][0]["caption"], cards["caption"]);
    EXPECT_EQ(response["cards"][0]["deadline"], cards["deadline"]);
    EXPECT_EQ(response["cards"][0]["column_id"], cards["column_id"]);
}

TEST(TestRemoveCard, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json response = cl.removeCard(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestUpdateCard, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json request = {{"id", id}, {"column_id", 4}};
    json response = cl.updateCard(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["cards"][0]["id"], id);
    EXPECT_EQ(response["cards"][0]["column_id"], request["column_id"]);
}

TEST(TestUpdateCard, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json request = {{"id", id}, {"column_id", 4}};
    json response = cl.updateCard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestUpdateCard, columnNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json request = {{"id", id}, {"column_id", 1111}};
    json response = cl.updateCard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardInfo, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.getCardInfo(id);
    json cards = TestEnvironment::getTestDataCards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["cards"][0]["id"], id);
    EXPECT_EQ(response["cards"][0]["name"], cards[0]["name"]);
    EXPECT_EQ(response["cards"][0]["caption"], cards[0]["caption"]);
    EXPECT_EQ(response["cards"][0]["deadline"], cards[0]["deadline"]);
    EXPECT_EQ(response["cards"][0]["column_id"], cards[0]["column_id"]);
}

TEST(TestGetCardInfo, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json response = cl.getCardInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardCheckLists, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.getCardCheckLists(id);
    json check_lists = TestEnvironment::getTestDataCheckLists(),
         check_lists_items = TestEnvironment::getTestDataCheckListsItems();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["check_lists"][0]["name"], check_lists[0]["name"]);
    EXPECT_EQ(response["check_lists"][0]["card_id"], check_lists[0]["card_id"]);
    EXPECT_EQ(response["check_lists_items"][0]["name"], check_lists_items[3]["name"]);
    EXPECT_EQ(response["check_lists_items"][0]["is_checked"], check_lists_items[3]["is_checked"]);
    EXPECT_EQ(response["check_lists_items"][0]["check_list_id"], check_lists_items[3]["check_list_id"]);
    EXPECT_EQ(response["check_lists_items"][0]["name"], check_lists_items[4]["name"]);
    EXPECT_EQ(response["check_lists_items"][0]["is_checked"], check_lists_items[4]["is_checked"]);
    EXPECT_EQ(response["check_lists_items"][0]["check_list_id"], check_lists_items[4]["check_list_id"]);
}

TEST(TestGetCardCheckLists, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json response = cl.getCardCheckLists(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardTags, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.getCardTags(id);
    json tags = TestEnvironment::getTestDataTags();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["tags"][0]["name"], tags[2]["name"]);
    EXPECT_EQ(response["tags"][0]["color"], tags[2]["color"]);
    EXPECT_EQ(response["tags"][0]["card_id"], tags[2]["card_id"]);
}

TEST(TestGetCardTags, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1111;
    json response = cl.getCardTags(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardColumn, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.getCardColumn(id);
    json cards = TestEnvironment::getTestDataTags();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["cards"][0]["column_id"], cards[0]["column_id"]);
}

TEST(TestGetCardColumn, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1111;
    json response = cl.getCardColumn(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestAddTag, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t card_id = 1;
    json request = {{"name", "abc"}, {"color", "blue"}, {"card_id", card_id}};
    json response = cl.addTag(card_id);
    json tags = TestEnvironment::getTestDataTags();
    size_t tag_id = tags.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["tags"][0]["id"], tag_id);
    EXPECT_EQ(response["tags"][0]["name"], request["name"]);
    EXPECT_EQ(response["tags"][0]["color"], request["color"]);
    EXPECT_EQ(response["tags"][0]["card_id"], request["card_id"]);
}

TEST(TestAddTag, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1111;
    json request = {{"name", "abc"}, {"color", "blue"}, {"card_id", id}};
    json response = cl.addTag(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveTag, tagExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.removeTag(id);
    json tags = TestEnvironment::getTestDataTags();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["tags"][0]["id"], id);
    EXPECT_EQ(response["tags"][0]["name"], tags[0]["name"]);
    EXPECT_EQ(response["tags"][0]["color"], tags[0]["color"]);
    EXPECT_EQ(response["tags"][0]["card_id"], tags[0]["tags"]);
}

TEST(TestRemoveTag, tagNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.removeTag(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestAddCheckList, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t card_id = 1;
    json request = {{"name", "for me"}, {"card_id", card_id}};
    json response = cl.addCheckList(request);
    json check_lists = TestEnvironment::getTestDataCheckLists();
    size_t check_list_id = check_lists.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["check_lists"][0]["id"], check_list_id);
    EXPECT_EQ(response["check_lists"][0]["name"], request["name"]);
    EXPECT_EQ(response["check_lists"][0]["card_id"], request["card_id"]);
}

TEST(TestAddCheckList, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t card_id = 11111;
    json request = {{"name", "for me"}, {"card_id", card_id}};
    json response = cl.addCheckList(card_id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveCheckList, checkListExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.addCheckList(id);
    json check_lists = TestEnvironment::getTestDataCheckLists();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["check_lists"][0]["id"], id);
    EXPECT_EQ(response["check_lists"][0]["name"], check_lists[0]["name"]);
    EXPECT_EQ(response["check_lists"][0]["color"], check_lists[0]["color"]);
    EXPECT_EQ(response["check_lists"][0]["card_id"], check_lists[0]["card_id"]);
}

TEST(TestRemoveCheckList, checkListNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 11111;
    json response = cl.addCheckList(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestAddCheckListItem, checkListExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t check_list_id = 1;
    json request = {{"name", "done"}, {"is_checked", false}, {"check_list_id", check_list_id}};
    json response = cl.addCheckListItem(request);
    json check_lists_items = TestEnvironment::getTestDataCheckLists();
    size_t check_lists_item_id = check_lists_items.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["check_lists_items"][0]["id"], check_lists_item_id);
    EXPECT_EQ(response["check_lists_items"][0]["name"], request["name"]);
    EXPECT_EQ(response["check_lists_items"][0]["is_checked"], request["is_checked"]);
    EXPECT_EQ(response["check_lists_items"][0]["check_list_id"], request["check_list_id"]);
}

TEST(TestAddCheckListItem, checkListNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t check_list_id = 11111;
    json request = {{"name", "done"}, {"is_checked", false}, {"check_list_id", check_list_id}};
    json response = cl.addCheckListItem(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveCheckListItem, checkListItemExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.removeCheckListItem(id);
    json check_lists_items = TestEnvironment::getTestDataCheckListsItems();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["check_lists"][0]["id"], id);
    EXPECT_EQ(response["check_lists_items"][0]["name"], check_lists_items[0]["name"]);
    EXPECT_EQ(response["check_lists_items"][0]["is_checked"], check_lists_items[0]["is_checked"]);
    EXPECT_EQ(response["check_lists_items"][0]["check_list_id"], check_lists_items[0]["check_list_id"]);
}

TEST(TestRemoveCheckListItem, checkListItemNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 11111;
    json response = cl.removeCheckListItem(id);

    EXPECT_EQ(response["status"], "error");
}