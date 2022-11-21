#include "main_manager.h"

MainManager::MainManager() {
  netClient = new HttpClient();
}

MainManager::~MainManager() {
  delete netClient;
}
