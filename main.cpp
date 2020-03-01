#include "snake.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Snake s;
  return a.exec();
}
