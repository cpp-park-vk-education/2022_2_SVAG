#include <QApplication>

#include "main_manager.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainManager mm;

  std::cout << "App started.." << std::endl;

  a.exec();

  std::cout << "Exit.." << std::endl;

  return 0;
}
