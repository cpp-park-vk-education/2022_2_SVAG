
std::string DatabaseInteraction::on_login(json msg_json)
{
    json result;
    json result = cl.checkUserValidation(msg_json);
    return convert(result);
}

std::string DatabaseInteraction::analyze_msg(json msg_json)
    {
        if (msg_json["cmd"] == "database_get") return on_get_content(msg_json);
        else if (msg_json["cmd"] == "database_create") return on_create_content(msg_json);
        else if (msg_json["cmd"] == "database_change") return on_change_content(msg_json);
        else if (msg_json["cmd"] == "database_delete") return on_delete_content(msg_json);
        else return on_invalid_msg();
    }

std::string DatabaseInteraction::on_get_content(json msg_json) 
{
    json result;
    if (msg_json["content"] == "board_info")
    {
        result = cl.getBoardInfo(msg_json["board_id"]);
    }
    else if (msg_json["content"] == "board_columns")
    {
        result = cl.getBoardColumns(msg_json["board_id"]);
    }
    else if (msg_json["content"] == "board_users")
    {
        result = cl.getBoardUsers(msg_json["board_id"]);
    }
    else if (msg_json["content"] == "board_column")
    {
        result = cl.getBoardColumn(msg_json["board_id"],msg_json["column_id"]);
    }
    else if (msg_json["content"] == "user_info")
    {
        result = cl.getUserInfo(msg_json["user_id"]);
    }
    else if (msg_json["content"] == "user_boards")
    {
        result = cl.getUserBoards(msg_json["user_id"]);
    }
    else if (msg_json["content"] == "card_info")
    {
        result = cl.getCardInfo(msg_json["card_id"]);
    }
    else if (msg_json["content"] == "card_checklists")
    {
        result = cl.getCardCheckLists(msg_json["card_id"]);
    }
    else if (msg_json["content"] == "card_tags")
    {
        result = cl.getCardTags(msg_json["card_id"]);
    }
    else if (msg_json["content"] == "card_column")
    {
        result = cl.getCardColumn(msg_json["card_id"]);
    }
    return convert(result);
}

std::string DatabaseInteraction::on_create_content(json msg_json)
{
    json data = json::parse(msg_json["data"]);
    json result;
    if (msg_json["content"] == "board")
    {
        result = cl.addboard(data);
    }
    else if (msg_json["content"] == "user")
    {
        result = cl.adduser(data);
    }
    else if (msg_json["content"] == "column")
    {
        result = cl.addcolumn(data);
    }
    else if (msg_json["content"] == "card")
    {
        result = cl.addcard(data);
    }
    else if (msg_json["content"] == "tag")
    {
        result = cl.addtag(data);
    }
    else if (msg_json["content"] == "checklist")
    {
        result = cl.addchecklist(data);
    }
    else if (msg_json["content"] == "checklist")
    {
        result = cl.addchecklistitem(data);
    }
    return convert(result);
}

std::string DatabaseInteraction::on_change_content(json msg_json)
{
    json data = json::parse(msg_json["data"]);
    json result;
    if (msg_json["content"] == "board")
    {
        result = cl.updateboard(data);
    }
    else if (msg_json["content"] == "user")
    {
        result = cl.updateuser(data);
    }
    else if (msg_json["content"] == "card")
    {
        result = cl.updatecard(data);
    }
    return convert(result);
}

std::string DatabaseInteraction::on_delete_content(json msg_json)
{
    json result;
    if (msg_json["content"] == "board")
    {
        result = cl.removeboard(msg_json["board_id"]);
    }
    else if (msg_json["content"] == "user")
    {
        result = cl.removeuser(msg_json["user_id"]);
    }
    else if (msg_json["content"] == "card")
    {
        result = cl.removecard(msg_json["card_id"]);
    }
    else if (msg_json["content"] == "tag")
    {
        result = cl.removetag(msg_json["tag_id"]);
    }
    else if (msg_json["content"] == "checklist")
    {
        result = cl.removechecklist(msg_json["checklist_id"]);
    }
    else if (msg_json["content"] == "checklist")
    {
        result = cl.removechecklistitem(msg_json["checklist_item_id"]);
    }
    return convert(result);
}

std::string DatabaseInteraction::on_invalid_msg()
{
    json result;
    result["response"] = "invalid msg";
    return convert(result);
}