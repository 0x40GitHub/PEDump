#ifndef FORMNTHEADERS_H
#define FORMNTHEADERS_H

#include <QWidget>
#include <windows.h>
namespace Ui {
  class FormNTHeaders;
}

class FormNTHeaders : public QWidget
{
  Q_OBJECT

public:
  explicit FormNTHeaders(QWidget *parent = nullptr);
  ~FormNTHeaders();
  void ShowInfo(PIMAGE_NT_HEADERS pimage_nt_headers, LPVOID ImageBase);

private:
  Ui::FormNTHeaders *ui;
};

#endif // FORMNTHEADERS_H
