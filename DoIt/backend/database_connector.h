#pragma once

#include "PostgreDataBase.h"
#include "BoardDataBase.h"

std::shared_ptr<PostgreDataBase> getPgClient();

BoardDataBase getBoardClient();