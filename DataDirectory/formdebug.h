#ifndef FORMDEBUG_H
#define FORMDEBUG_H

#include <QWidget>

namespace Ui {
  class FormDebug;
}

class FormDebug : public QWidget
{
  Q_OBJECT

public:
  explicit FormDebug(QWidget *parent = nullptr);
  ~FormDebug();

private:
  Ui::FormDebug *ui;
};

#endif // FORMDEBUG_H
