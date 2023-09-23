#ifndef FORMCLRRUNTIMEHEADER_H
#define FORMCLRRUNTIMEHEADER_H

#include <QWidget>

namespace Ui {
  class FormCLRRuntimeHeader;
}

class FormCLRRuntimeHeader : public QWidget
{
  Q_OBJECT

public:
  explicit FormCLRRuntimeHeader(QWidget *parent = nullptr);
  ~FormCLRRuntimeHeader();

private:
  Ui::FormCLRRuntimeHeader *ui;
};

#endif // FORMCLRRUNTIMEHEADER_H
