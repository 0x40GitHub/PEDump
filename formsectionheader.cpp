#include "formsectionheader.h"
#include "ui_formsectionheader.h"

FormSectionHeader::FormSectionHeader(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormSectionHeader)
{
  ui->setupUi(this);
  // section characteristic
  QMap<DWORD, QCheckBox*> SectionCharacteristics;
  SectionCharacteristics[0x00000000] = ui->groupBox->findChild<QCheckBox*>("checkBox_1");
  for (int i = 2; i <= 21; i++) {
      SectionCharacteristics.insert(pow(2,i-1), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i)));
    }
  for (int i = 25; i <= 32; i++) {
      SectionCharacteristics.insert(pow(2,i-1), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i)));
    }

  QMap<DWORD, QCheckBox*>::Iterator iter;
  iter = SectionCharacteristics.begin();
  while (iter != SectionCharacteristics.end()) {
      connect(iter.value(), SIGNAL(stateChanged(int)), this, SLOT(checkBox_stateChanged(int)));
      iter++;
    }
}

FormSectionHeader::~FormSectionHeader()
{
  delete ui;
}

void FormSectionHeader::ShowInfo(PIMAGE_SECTION_HEADER pimage_section_header, LPVOID ImageBase)
{
  // Name
  ui->tableWidget->setItem(0,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->Name - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(0,
                           1,
                           new QTableWidgetItem(QString::fromStdString((char*)pimage_section_header->Name)));
  // VirtualSize
  ui->tableWidget->setItem(1,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->Misc.VirtualSize - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(1,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->Misc.VirtualSize, 16)));

  // VirtualAddress
  ui->tableWidget->setItem(2,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->VirtualAddress - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(2,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->VirtualAddress, 16)));

  // SizeOfRawData
  ui->tableWidget->setItem(3,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->SizeOfRawData - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(3,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->SizeOfRawData, 16)));

  // PointerToRawData
  ui->tableWidget->setItem(4,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->PointerToRawData - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(4,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->PointerToRawData, 16)));

  // PointerToRelocations
  ui->tableWidget->setItem(5,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->PointerToRelocations - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(5,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->PointerToRelocations)));

  //  PointerToLinenumbers
  ui->tableWidget->setItem(6,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->PointerToLinenumbers - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(6,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->PointerToLinenumbers, 16)));

  // NumberOfRelocations
  ui->tableWidget->setItem(7,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->NumberOfRelocations - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(7,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->NumberOfRelocations, 16)));

  // NumberOfLinenumbers
  ui->tableWidget->setItem(8,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->NumberOfLinenumbers - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(8,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->NumberOfLinenumbers, 16)));

  // Characteristics
  ui->tableWidget->setItem(9,
                           0,
                           new QTableWidgetItem(QString::number((DWORD)&pimage_section_header->Characteristics - (DWORD)ImageBase, 16)));
  ui->tableWidget->setItem(9,
                           1,
                           new QTableWidgetItem(QString::number(pimage_section_header->Characteristics, 16)));

  // section characteristic
  QMap<DWORD, QCheckBox*> SectionCharacteristics;
  SectionCharacteristics[0x00000000] = ui->groupBox->findChild<QCheckBox*>("checkBox_1");
  for (int i = 2; i <= 21; i++) {
      SectionCharacteristics.insert(pow(2,i-1), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i)));
    }
  for (int i = 25; i <= 32; i++) {
      SectionCharacteristics.insert(pow(2,i-1), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i)));
    }

  QMap<DWORD, QCheckBox*>::Iterator iter;
  iter = SectionCharacteristics.begin();

  while (iter != SectionCharacteristics.end()) {
      if ((pimage_section_header->Characteristics & iter.key()) != 0) {
          iter.value()->setChecked(true);
        }
      iter++;
    }

}

void FormSectionHeader::checkBox_stateChanged(int arg)
{
  DWORD characteristic = ui->tableWidget->item(9, 0)->text().toInt();
  // section characteristic
  QMap<DWORD, QCheckBox*> SectionCharacteristics;
  SectionCharacteristics[0x00000000] = ui->groupBox->findChild<QCheckBox*>("checkBox_1");
  for (int i = 2; i <= 21; i++) {
      SectionCharacteristics.insert(pow(2,i-2), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i)));
    }
  for (int i = 25; i <= 32; i++) {
      SectionCharacteristics.insert(pow(2,i-1), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i)));
    }

  QMap<DWORD, QCheckBox*>::Iterator iter;
  iter = SectionCharacteristics.begin();
  while (iter != SectionCharacteristics.end()) {
      if (iter.value()->isChecked()) {
          characteristic |= iter.key();
        } else {
          characteristic &= (~iter.key());
        }
      iter++;
    }
  ui->tableWidget->setItem(9, 1, new QTableWidgetItem(QString::number(characteristic, 16)));
}



