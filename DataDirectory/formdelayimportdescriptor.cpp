#include "formdelayimportdescriptor.h"
#include "ui_formdelayimportdescriptor.h"

FormDelayImportDescriptor::FormDelayImportDescriptor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormDelayImportDescriptor)
{
  ui->setupUi(this);
}

FormDelayImportDescriptor::~FormDelayImportDescriptor()
{
  delete ui;
}
