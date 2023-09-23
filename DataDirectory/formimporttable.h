#ifndef FORMIMPORTTABLE_H
#define FORMIMPORTTABLE_H

#include <QWidget>
#include <windows.h>
#include <QTableWidgetItem>

namespace Ui {
  class FormImportTable;
}

class FormImportTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormImportTable(QWidget *parent = nullptr);
  ~FormImportTable();
  void ShowInfo(LPVOID ImageBase);

private slots:


  void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
  Ui::FormImportTable *ui;
  LPVOID ImageBase;
};

#endif // FORMIMPORTTABLE_H
