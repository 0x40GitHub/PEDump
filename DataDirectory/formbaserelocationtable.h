#ifndef FORMBASERELOCATIONTABLE_H
#define FORMBASERELOCATIONTABLE_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormBaseRelocationTable;
}

class FormBaseRelocationTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormBaseRelocationTable(QWidget *parent = nullptr);
  ~FormBaseRelocationTable();
  void ShowInfo(LPVOID ImageBase);

private:
  Ui::FormBaseRelocationTable *ui;
};

#endif // FORMBASERELOCATIONTABLE_H
