#ifndef PEDUMPMAINWINDOW_H
#define PEDUMPMAINWINDOW_H

#include <QMainWindow>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class PEDumpMainWindow;}
QT_END_NAMESPACE

class PEDumpMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  PEDumpMainWindow(QWidget *parent = nullptr);
  ~PEDumpMainWindow();
  void dragEnterEvent(QDragEnterEvent*event) Q_DECL_OVERRIDE; //文件拖拽到窗体内，触发
  void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE; //文件拖拽到窗体内，释放，触发

private slots:
  void on_actionOpen_triggered();

  void on_actionMS_DOS_Header_triggered();

  void on_actionNT_Headers_triggered();

  void on_actionFile_Header_triggered();

  void on_actionOptionalHeader_triggered();

  void on_actionSections_triggered();

  void on_actionDataDirectory_triggered();

  void on_actionSavePEFile_triggered();

  void on_actionEditPE_triggered();

  void on_actionRVAToFOA_triggered();

signals:
  void SendImageBase(LPVOID ImageBase);

private:
  Ui::PEDumpMainWindow *ui;
};
#endif // PEDUMPMAINWINDOW_H
