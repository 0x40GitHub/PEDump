#ifndef FORMDATADIRECTORY_H
#define FORMDATADIRECTORY_H

#include <QWidget>
#include <windows.h>
namespace Ui {
  class FormDataDirectory;
}

class FormDataDirectory : public QWidget
{
  Q_OBJECT

public:
  explicit FormDataDirectory(QWidget *parent = nullptr);
  ~FormDataDirectory();
  void ShowInfo(LPVOID ImageBase);

private slots:
  void on_pushButtonExportTable_clicked();

  void on_pushButtonImportTable_clicked();

  void on_pushButton_11_clicked();

  void on_pushButton_3_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_16_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_10_clicked();

  void on_pushButton_12_clicked();

  void on_pushButton_13_clicked();

  void on_pushButton_14_clicked();

public slots:
  void ReceiveImageBase(LPVOID ImageBase);
private:
  Ui::FormDataDirectory *ui;
  LPVOID ImageBase;
};

#endif // FORMDATADIRECTORY_H
