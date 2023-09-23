#include "formloadconfigtable.h"
#include "ui_formloadconfigtable.h"

FormLoadConfigTable::FormLoadConfigTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormLoadConfigTable)
{
  ui->setupUi(this);
}

FormLoadConfigTable::~FormLoadConfigTable()
{
  delete ui;
}
