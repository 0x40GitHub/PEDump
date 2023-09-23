#ifndef FORMSECTIONS_H
#define FORMSECTIONS_H

#include <QWidget>
#include <windows.h>

namespace Ui {
  class FormSections;
}

class FormSections : public QWidget
{
  Q_OBJECT

public:
  explicit FormSections(QWidget *parent = nullptr);
  ~FormSections();
  void ShowInfo(LPVOID ImageBase);

private:
  Ui::FormSections *ui;
};

#endif // FORMSECTIONS_H
