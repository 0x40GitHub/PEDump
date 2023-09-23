#include "formcertificatetable.h"
#include "ui_formcertificatetable.h"

FormCertificateTable::FormCertificateTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormCertificateTable)
{
  ui->setupUi(this);
}

FormCertificateTable::~FormCertificateTable()
{
  delete ui;
}
