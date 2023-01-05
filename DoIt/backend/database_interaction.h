#pragma once
#include "database_connector.h"
#include "BoardDataBase.h"
#include "CardDataBase.h"
#include "UserDataBase.h"

#include "json.hpp"
using json = nlohmann::json;

struct json_to_string_response_convert
{
    std::string operator()(json j)
    {
        std::string response = j.dump();
        response = response + "\n";
        return response;
    }
};

class DatabaseInteraction
{
public:
    DatabaseInteraction(): cl(getBoardClient()), clUser(getUserClient()), clCard(getCardClient()) {}
    std::string analyze_msg(json msg_json);
    std::string on_login(json msg_json);
private:
    std::string on_get_content(json msg_json);
    std::string on_create_content(json msg_json);
    std::string on_change_content(json msg_json);
    std::string on_delete_content(json msg_json);
    std::string on_invalid_msg();
private:
    json_to_string_response_convert convert;
    BoardDataBase cl;
    CardDataBase clCard;
    UserDataBase clUser;
};