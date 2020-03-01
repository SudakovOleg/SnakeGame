#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QTimer>
#include "deskwnd.h"

struct cell
{
  int x;
  int y;
};

class Snake : QObject
{
  Q_OBJECT
public:
  Snake();
public slots:
  void direction(int);
private:
  void directionChange();
  void generateApple();
  bool isEat();
  void burnOnBord();
  bool isGameOver();
  void restart();
private slots:
  void turn();
signals:
  void newScore(int);
private:
  int tact;
  int directionNext;
  int directionNow;
  Board* board;
  QTimer* timer;
  cell* apple;
  QList<cell>* cells;
};

#endif // SNAKE_H
