#pragma once

#include <iostream>
#include <vector>

const std::string userTableName = "users";
const std::vector<std::string> userTableColumns = {"id", "username", "email", "password", "avatar"};

const std::string boardTableName = "boards";
const std::vector<std::string> boardTableColumns = {"id", "name", "caption", "background"};

const std::string users2boardsTableName = "users2boards";
const std::vector<std::string> users2boardsTableColumns = {"user_id", "board_id"};