#ifndef FORMTLSTABLE_H
#define FORMTLSTABLE_H

#include <QWidget>

namespace Ui {
  class FormTLSTable;
}

class FormTLSTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormTLSTable(QWidget *parent = nullptr);
  ~FormTLSTable();

private:
  Ui::FormTLSTable *ui;
};

#endif // FORMTLSTABLE_H
