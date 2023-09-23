#include "formglobalptr.h"
#include "ui_formglobalptr.h"

FormGlobalPtr::FormGlobalPtr(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormGlobalPtr)
{
  ui->setupUi(this);
}

FormGlobalPtr::~FormGlobalPtr()
{
  delete ui;
}
