#ifndef FORMRVATOFOA_H
#define FORMRVATOFOA_H

#include <QWidget>
#include <windows.h>
namespace Ui {
  class FormRVAToFOA;
}

class FormRVAToFOA : public QWidget
{
  Q_OBJECT

public:
  explicit FormRVAToFOA(QWidget *parent = nullptr);
  ~FormRVAToFOA();
  void ShowInfo(LPVOID ImageBase);

private slots:
  void on_pushButton_clicked();

private:
  Ui::FormRVAToFOA *ui;
  LPVOID ImageBse;
};

#endif // FORMRVATOFOA_H
