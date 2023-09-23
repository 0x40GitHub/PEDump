#ifndef FORMEXCEPTIONTABLE_H
#define FORMEXCEPTIONTABLE_H

#include <QWidget>

namespace Ui {
  class FormExceptionTable;
}

class FormExceptionTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormExceptionTable(QWidget *parent = nullptr);
  ~FormExceptionTable();

private:
  Ui::FormExceptionTable *ui;
};

#endif // FORMEXCEPTIONTABLE_H
