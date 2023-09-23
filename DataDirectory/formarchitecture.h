#ifndef FORMARCHITECTURE_H
#define FORMARCHITECTURE_H

#include <QWidget>

namespace Ui {
  class FormArchitecture;
}

class FormArchitecture : public QWidget
{
  Q_OBJECT

public:
  explicit FormArchitecture(QWidget *parent = nullptr);
  ~FormArchitecture();

private:
  Ui::FormArchitecture *ui;
};

#endif // FORMARCHITECTURE_H
