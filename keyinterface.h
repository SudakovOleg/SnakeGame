#ifndef KEYINTERFACE_H
#define KEYINTERFACE_H

#include <QWidget>
#include <QKeyEvent>

class KeyInterface : public QWidget
{
  Q_OBJECT
public:
  KeyInterface();
signals:
  void pressKey(int);
private:
  virtual void keyPressEvent(QKeyEvent *event);
};

#endif // KEYINTERFACE_H
