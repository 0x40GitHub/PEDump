#ifndef FORMEXPORTTABLE_H
#define FORMEXPORTTABLE_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormExportTable;
}

class FormExportTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormExportTable(QWidget *parent = nullptr);
  ~FormExportTable();
  void ShowInfo(LPVOID ImageBase);


private:
  Ui::FormExportTable *ui;

};

#endif // FORMEXPORTTABLE_H
