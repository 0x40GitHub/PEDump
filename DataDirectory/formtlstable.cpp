#include "formtlstable.h"
#include "ui_formtlstable.h"

FormTLSTable::FormTLSTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormTLSTable)
{
  ui->setupUi(this);
}

FormTLSTable::~FormTLSTable()
{
  delete ui;
}
