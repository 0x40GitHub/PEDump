#ifndef FORMSECTIONHEADER_H
#define FORMSECTIONHEADER_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormSectionHeader;
}

class FormSectionHeader : public QWidget
{
  Q_OBJECT

public:
  explicit FormSectionHeader(QWidget *parent = nullptr);
  ~FormSectionHeader();
  void ShowInfo(PIMAGE_SECTION_HEADER pimage_section_header, LPVOID ImageBase);

private:
  Ui::FormSectionHeader *ui;

private slots:
  void checkBox_stateChanged(int arg);
};

#endif // FORMSECTIONHEADER_H
