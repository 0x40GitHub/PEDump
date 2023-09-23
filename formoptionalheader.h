#ifndef FORMOPTIONALHEADER_H
#define FORMOPTIONALHEADER_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormOptionalHeader;
}

class FormOptionalHeader : public QWidget
{
  Q_OBJECT

public:
  explicit FormOptionalHeader(QWidget *parent = nullptr);
  ~FormOptionalHeader();
  void ShowInfo(PIMAGE_OPTIONAL_HEADER pimage_optional_header, LPVOID ImageBase);

private slots:
  void on_comboBoxSubsystem_currentTextChanged(const QString &arg1);
  void checkBox_stateChanged(int arg);

private:
  Ui::FormOptionalHeader *ui;
};

#endif // FORMOPTIONALHEADER_H
