#include "formarchitecture.h"
#include "ui_formarchitecture.h"

FormArchitecture::FormArchitecture(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormArchitecture)
{
  ui->setupUi(this);
}

FormArchitecture::~FormArchitecture()
{
  delete ui;
}
