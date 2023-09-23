#ifndef FORMEDITPEFILE_H
#define FORMEDITPEFILE_H

#include <QWidget>
#include <windows.h>
namespace Ui {
  class FormEditPEFile;
}

class FormEditPEFile : public QWidget
{
  Q_OBJECT

public:
  explicit FormEditPEFile(QWidget *parent = nullptr);
  ~FormEditPEFile();

private slots:
  void on_pushButtonInsertSection_clicked();

  void on_pushButtonSave_clicked();




  void on_pushButtonSaveMerge_clicked();

  void on_pushButtonSaveExpandSection_clicked();

  void on_pushButtonExpandSection_clicked();

  void on_pushButtonMerge_clicked();

private:
  Ui::FormEditPEFile *ui;
  LPVOID ImageBase;
public slots:
  void ReceiveImageBase(LPVOID ImageBase);
};

#endif // FORMEDITPEFILE_H
