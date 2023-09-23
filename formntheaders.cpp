#include "formntheaders.h"
#include "ui_formntheaders.h"
#include "peutils.h"

FormNTHeaders::FormNTHeaders(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormNTHeaders)
{
  ui->setupUi(this);
}

FormNTHeaders::~FormNTHeaders()
{
  delete ui;
}

void FormNTHeaders::ShowInfo(PIMAGE_NT_HEADERS pimage_nt_headers, LPVOID ImageBase)
{

  ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&pimage_nt_headers->Signature - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString("%1").arg(pimage_nt_headers->Signature, 8, 16, QLatin1Char('0'))));


  ui->tableWidget->setItem(1, 0, new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&pimage_nt_headers->FileHeader - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&pimage_nt_headers->FileHeader - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));

  ui->tableWidget->setItem(2, 0, new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&pimage_nt_headers->OptionalHeader - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&pimage_nt_headers->OptionalHeader - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
}
