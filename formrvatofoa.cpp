#include "formrvatofoa.h"
#include "ui_formrvatofoa.h"
#include <windows.h>
#include "peutils.h"
#include <QDebug>
#include <QRegExpValidator>
FormRVAToFOA::FormRVAToFOA(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormRVAToFOA)
{
  ui->setupUi(this);
  QRegExp regx("[A-Fa-f0-9]{4}");
  QValidator *validator = new QRegExpValidator(regx, ui->lineEditFOA);
  QValidator *validator1 = new QRegExpValidator(regx, ui->lineEditFOA);
  ui->lineEditRVA->setValidator(validator);
  ui->lineEditFOA->setValidator(validator1);
}

FormRVAToFOA::~FormRVAToFOA()
{
  delete ui;
}

void FormRVAToFOA::ShowInfo(LPVOID ImageBase)
{
  this->ImageBse = ImageBase;

}

void FormRVAToFOA::on_pushButton_clicked()
{
    DWORD RVA = 0;
    DWORD FOA = 0;
    if (!ui->lineEditRVA->text().isEmpty()) {
        RVA = ui->lineEditRVA->text().toInt(NULL, 16);
        FOA = RVAToFOA(this->ImageBse, RVA);
        ui->lineEditFOA->setText(QString::number(FOA, 16));
        ui->lineEditRVA->setText(QString(""));
      } else if (!ui->lineEditFOA->text().isEmpty()) {
        FOA = ui->lineEditFOA->text().toInt(NULL, 16);
        RVA = FOAToRVA(this->ImageBse, FOA);
        ui->lineEditRVA->setText(QString::number(RVA, 16));
        ui->lineEditFOA->setText(QString(""));
      }
}

