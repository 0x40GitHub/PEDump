#ifndef FORMMSDOSHEADER_H
#define FORMMSDOSHEADER_H

#include <QWidget>
#include <windows.h>
namespace Ui {
  class FormMSDOSHeader;
}

class FormMSDOSHeader : public QWidget
{
  Q_OBJECT

public:
  explicit FormMSDOSHeader(QWidget *parent = nullptr);
  ~FormMSDOSHeader();
  void ShowInfo(PIMAGE_DOS_HEADER pimage_dos_header);

private:
  Ui::FormMSDOSHeader *ui;
};

#endif // FORMMSDOSHEADER_H
