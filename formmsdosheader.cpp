#include "formmsdosheader.h"
#include "ui_formmsdosheader.h"

FormMSDOSHeader::FormMSDOSHeader(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormMSDOSHeader)
{
  ui->setupUi(this);

}

FormMSDOSHeader::~FormMSDOSHeader()
{
  delete ui;
}

// MS-DOS Header info
void FormMSDOSHeader::ShowInfo(PIMAGE_DOS_HEADER pimage_dos_header){
  int rowCount = ui->tableWidget->rowCount();
  DWORD baseAddr = (DWORD)pimage_dos_header;

  int i;
  for (i = 0; i < rowCount-1; i++) {
      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i * 2, 8, 16, QLatin1Char('0'))));
      ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(*(WORD*)(baseAddr + i * 2), 8, 16, QLatin1Char('0'))));
    }


  ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(i * 2, 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(*(DWORD*)(baseAddr + i * 2), 8, 16, QLatin1Char('0'))));
}


