#ifndef FORMFILEHEADER_H
#define FORMFILEHEADER_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormFileHeader;
}

class FormFileHeader : public QWidget
{
  Q_OBJECT

public:
  explicit FormFileHeader(QWidget *parent = nullptr);
  ~FormFileHeader();
  void ShowInfo(PIMAGE_FILE_HEADER pimage_file_header, LPVOID ImageBase);
  LPVOID ImageBase;


private slots:
  void on_comboBox_currentTextChanged(const QString &arg1);

  void checkBox_stateChanged(int checked);


private:
  Ui::FormFileHeader *ui;
};

#endif // FORMFILEHEADER_H
