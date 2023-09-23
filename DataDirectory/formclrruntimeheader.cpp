#include "formclrruntimeheader.h"
#include "ui_formclrruntimeheader.h"

FormCLRRuntimeHeader::FormCLRRuntimeHeader(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormCLRRuntimeHeader)
{
  ui->setupUi(this);
}

FormCLRRuntimeHeader::~FormCLRRuntimeHeader()
{
  delete ui;
}
