#include "formdebug.h"
#include "ui_formdebug.h"

FormDebug::FormDebug(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormDebug)
{
  ui->setupUi(this);
}

FormDebug::~FormDebug()
{
  delete ui;
}
