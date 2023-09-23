#include "formexceptiontable.h"
#include "ui_formexceptiontable.h"

FormExceptionTable::FormExceptionTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormExceptionTable)
{
  ui->setupUi(this);
}

FormExceptionTable::~FormExceptionTable()
{
  delete ui;
}
