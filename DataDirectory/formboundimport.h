#ifndef FORMBOUNDIMPORT_H
#define FORMBOUNDIMPORT_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormBoundImport;
}

class FormBoundImport : public QWidget
{
  Q_OBJECT

public:
  explicit FormBoundImport(QWidget *parent = nullptr);
  ~FormBoundImport();
  int ShowInfo(LPVOID ImageBase);

private:
  Ui::FormBoundImport *ui;
};

#endif // FORMBOUNDIMPORT_H
