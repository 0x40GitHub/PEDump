#ifndef FORMDELAYIMPORTDESCRIPTOR_H
#define FORMDELAYIMPORTDESCRIPTOR_H

#include <QWidget>

namespace Ui {
  class FormDelayImportDescriptor;
}

class FormDelayImportDescriptor : public QWidget
{
  Q_OBJECT

public:
  explicit FormDelayImportDescriptor(QWidget *parent = nullptr);
  ~FormDelayImportDescriptor();

private:
  Ui::FormDelayImportDescriptor *ui;
};

#endif // FORMDELAYIMPORTDESCRIPTOR_H
