#ifndef FORMRESOURCETABLE_H
#define FORMRESOURCETABLE_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormResourceTable;
}

class FormResourceTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormResourceTable(QWidget *parent = nullptr);
  ~FormResourceTable();
  int ShowInfo(LPVOID ImageBase);

private:
  Ui::FormResourceTable *ui;
};

#endif // FORMRESOURCETABLE_H
