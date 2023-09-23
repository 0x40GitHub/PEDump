#ifndef FORMGLOBALPTR_H
#define FORMGLOBALPTR_H

#include <QWidget>

namespace Ui {
  class FormGlobalPtr;
}

class FormGlobalPtr : public QWidget
{
  Q_OBJECT

public:
  explicit FormGlobalPtr(QWidget *parent = nullptr);
  ~FormGlobalPtr();

private:
  Ui::FormGlobalPtr *ui;
};

#endif // FORMGLOBALPTR_H
