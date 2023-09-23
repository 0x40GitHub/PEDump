#include "formiat.h"
#include "ui_formiat.h"

FormIAT::FormIAT(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormIAT)
{
  ui->setupUi(this);
}

FormIAT::~FormIAT()
{
  delete ui;
}
