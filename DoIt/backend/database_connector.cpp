#include "database_connector.h"

std::shared_ptr<PostgreDataBase> getPgClient() {
    static std::shared_ptr<PostgreConnectParams> conParams =
        std::make_shared<PostgreConnectParams>("db_test", "postgres");

    static std::shared_ptr<PostgreDataBase> pg = std::make_shared<PostgreDataBase>(conParams);

    return pg;
}

BoardDataBase getBoardClient() {
    static std::shared_ptr<DataBase> pg = getPgClient();
    static BoardDataBase cl(pg);
    return cl;
}