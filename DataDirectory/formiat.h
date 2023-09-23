#ifndef FORMIAT_H
#define FORMIAT_H

#include <QWidget>

namespace Ui {
  class FormIAT;
}

class FormIAT : public QWidget
{
  Q_OBJECT

public:
  explicit FormIAT(QWidget *parent = nullptr);
  ~FormIAT();

private:
  Ui::FormIAT *ui;
};

#endif // FORMIAT_H
