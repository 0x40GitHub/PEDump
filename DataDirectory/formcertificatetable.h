#ifndef FORMCERTIFICATETABLE_H
#define FORMCERTIFICATETABLE_H

#include <QWidget>

namespace Ui {
  class FormCertificateTable;
}

class FormCertificateTable : public QWidget
{
  Q_OBJECT

public:
  explicit FormCertificateTable(QWidget *parent = nullptr);
  ~FormCertificateTable();

private:
  Ui::FormCertificateTable *ui;
};

#endif // FORMCERTIFICATETABLE_H
