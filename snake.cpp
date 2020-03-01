#include "snake.h"
#include <QMessageBox>
#include <QApplication>

#define SIZE_DESK 15
#define SPEED 250

Snake::Snake()
{
  //Инициализация объектов
  qsrand(QApplication::applicationPid());
  cells = new QList<cell>;
  apple = new cell;
  timer = new QTimer;
  board = new Board(nullptr, SIZE_DESK);
  connect(timer, SIGNAL(timeout()), SLOT(turn()));
  connect(board, SIGNAL(pressKey(int)), SLOT(direction(int)));
  connect(this, SIGNAL(newScore(int)), board, SLOT(score(int)));
  restart();
}

void Snake::direction(int dirn)
{
  directionNext = dirn;
}

//Метод изменения направления
void Snake::directionChange()
{
  if(directionNext > 0 && directionNext < 5)
  {
    if((directionNext%2 == 0 && directionNow%2 == 0) ||
       (directionNext%2 != 0 && directionNow%2 != 0))
      return;
    directionNow = directionNext;
  }
}

//Метод генерации яблока
void Snake::generateApple()
{
  bool place = true;
  while(place)
  {
    this->apple->x = qrand()%(SIZE_DESK-1) + 1;
    this->apple->y = qrand()%(SIZE_DESK-1) + 1;
    place = false;
    for(auto body_cell : *cells)
    {
      if(body_cell.x == apple->x && body_cell.y == apple->y)
        place = true;
    }
  }
}

//Метод проверки наличия яблока
bool Snake::isEat()
{
  return (cells->at(0).x == apple->x && cells->at(0).y == apple->y);
}

//Метод для вывода данных на поле
void Snake::burnOnBord()
{
  for(auto body_cell : *cells)
  {
    board->burn(body_cell.x, body_cell.y, "red");
  }
  board->burn(apple->x, apple->y, "green");
}

//Проверка на окончание игры
bool Snake::isGameOver()
{
  if(cells->first().x < 0 || cells->first().x >= SIZE_DESK)
  {
    QMessageBox::information(nullptr,"Game over", "Game over! Desk is very small, is't it? ");
    return true;
  }
  if(cells->first().y < 0 || cells->first().y >= SIZE_DESK)
  {
    QMessageBox::information(nullptr,"Game over", "Game over! Desk is very small, is't it? ");
    return true;
  }
    for(int i(1); i < cells->length(); i++)
    {
      if(cells->at(0).x == cells->at(i).x && cells->at(0).y == cells->at(i).y)
      {
        QMessageBox::information(nullptr, "Game over", "Game over! Snake eat herself!");
        return true;
      }
    }
    return false;
}

void Snake::restart()
{
  cells->clear();
  //Создание начальной змейки
  cell head;
  head.x = 10;
  head.y = 10;
  cells->push_back(head);
  cell body;
  body.x = 10;
  body.y = 11;
  cells->push_back(body);
  this->apple->x = 8;
  this->apple->y = 10;

  //Вывод поля для игры и подключение таймера
  board->show();
  board->clear();
  burnOnBord();
  directionNow = 4;
  directionNext = 4;
  tact = 0;
  timer->start(SPEED);
}

//Метод этапа хода
void Snake::turn()
{
  directionChange();
  if(!isEat())
  {
    cells->removeLast();
  }
  else
  {
    emit newScore(cells->length() + 1);
    generateApple();
  }
  switch(directionNow)
  {
    case 1:
    {
        cell head;
        head.x = cells->at(0).x;
        head.y = cells->at(0).y - 1;
        cells->push_front(head);
        break;
    }
    case 2:
    {
        cell head;
        head.x = cells->at(0).x + 1;
        head.y = cells->at(0).y;
        cells->push_front(head);
        break;
    }
    case 3:
    {
        cell head;
        head.x = cells->at(0).x;
        head.y = cells->at(0).y + 1;
        cells->push_front(head);
        break;
    }
    case 4:
    {
        cell head;
        head.x = cells->at(0).x - 1;
        head.y = cells->at(0).y;
        cells->push_front(head);
        break;
    }
    default:
      break;
  }
  if(!isGameOver())
  {
    board->clear();
    burnOnBord();
    timer->start(SPEED);
  }
  else
  {
    timer->stop();
    restart();
  }
}
