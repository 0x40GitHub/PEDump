#ifndef FORMLOADCONFIGTABLE_H
#define FORMLOADCONFIGTABLE_H

#include <QWidget>

namespace Ui {
  class FormLoadConfigTable;
}

class FormLoadConfigTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormLoadConfigTable(QWidget *parent = nullptr);
  ~FormLoadConfigTable();

private:
  Ui::FormLoadConfigTable *ui;
};

#endif // FORMLOADCONFIGTABLE_H
