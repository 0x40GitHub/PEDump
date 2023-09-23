#include "formoptionalheader.h"
#include "ui_formoptionalheader.h"
#include "peutils.h"
#include <QDebug>

FormOptionalHeader::FormOptionalHeader(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormOptionalHeader)
{
  ui->setupUi(this);
  QMap<DWORD, QCheckBox*> DllCharacteristics;
  for (int i = 0; i < 16; i++) {
      DllCharacteristics.insert(pow(2, i), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i+1)));
    }
  QMap<DWORD, QCheckBox*>::Iterator iter;
  iter = DllCharacteristics.begin();
  while (iter != DllCharacteristics.end()) {
      connect(iter.value(), SIGNAL(stateChanged(int)), this, SLOT(checkBox_stateChanged(int)));
      iter++;
    }
}

FormOptionalHeader::~FormOptionalHeader()
{
  delete ui;
}
QMap<DWORD, std::string> subSystems;
void FormOptionalHeader::ShowInfo(PIMAGE_OPTIONAL_HEADER pimage_optional_header, LPVOID ImageBase)
{
  // Magic
  ui->tableWidget->setItem(0,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->Magic, 16)));
  ui->tableWidget->setItem(0,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->Magic - (DWORD)ImageBase), 16)));
  // MajorLinkerVersion
  ui->tableWidget->setItem(1,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MajorLinkerVersion, 16)));
  ui->tableWidget->setItem(1,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MajorLinkerVersion - (DWORD)ImageBase), 16)));

  // MinorLinkerVersion
  ui->tableWidget->setItem(2,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MinorLinkerVersion, 16)));
  ui->tableWidget->setItem(2,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MinorLinkerVersion - (DWORD)ImageBase), 16)));

  // SizeOfCode
  ui->tableWidget->setItem(3,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfCode, 16)));
  ui->tableWidget->setItem(3,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfCode - (DWORD)ImageBase), 16)));

  // SizeOfInitializedData
  ui->tableWidget->setItem(4,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfInitializedData, 16)));
  ui->tableWidget->setItem(4,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfInitializedData - (DWORD)ImageBase), 16)));

  // SizeOfUninitializedData
  ui->tableWidget->setItem(5,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfUninitializedData, 16)));
  ui->tableWidget->setItem(5,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfUninitializedData - (DWORD)ImageBase), 16)));

  // AddressOfEntryPoint
  ui->tableWidget->setItem(6,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->AddressOfEntryPoint, 16)));
  ui->tableWidget->setItem(6,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->AddressOfEntryPoint - (DWORD)ImageBase), 16)));

  // BaseOfCode
  ui->tableWidget->setItem(7,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->BaseOfCode, 16)));
  ui->tableWidget->setItem(7,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->BaseOfCode - (DWORD)ImageBase), 16)));

  // BaseOfData
  ui->tableWidget->setItem(8,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->BaseOfData, 16)));
  ui->tableWidget->setItem(8,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->BaseOfData - (DWORD)ImageBase), 16)));

  // ImageBase
  ui->tableWidget->setItem(9,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->ImageBase, 16)));
   ui->tableWidget->setItem(9,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->ImageBase - (DWORD)ImageBase), 16)));

  // SectionAlignment
  ui->tableWidget->setItem(10,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SectionAlignment, 16)));
  ui->tableWidget->setItem(10,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SectionAlignment - (DWORD)ImageBase), 16)));

  // FileAlignment
  ui->tableWidget->setItem(11,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->FileAlignment, 16)));
  ui->tableWidget->setItem(11,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->FileAlignment - (DWORD)ImageBase), 16)));

  // MajorOperatingSystemVersion
  ui->tableWidget->setItem(12,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MajorOperatingSystemVersion, 16)));
  ui->tableWidget->setItem(12,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MajorOperatingSystemVersion - (DWORD)ImageBase), 16)));

  // MinorOperatingSystemVersion
  ui->tableWidget->setItem(13,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MinorOperatingSystemVersion, 16)));
  ui->tableWidget->setItem(13,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MinorOperatingSystemVersion - (DWORD)ImageBase), 16)));

  // MajorImageVersion
  ui->tableWidget->setItem(14,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MajorImageVersion, 16)));
  ui->tableWidget->setItem(14,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MajorImageVersion - (DWORD)ImageBase), 16)));

  // MinorImageVersion
  ui->tableWidget->setItem(15,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MinorImageVersion, 16)));
  ui->tableWidget->setItem(15,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MinorImageVersion - (DWORD)ImageBase), 16)));

  // MajorSubsystemVersion
  ui->tableWidget->setItem(16,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MajorSubsystemVersion, 16)));
  ui->tableWidget->setItem(16,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MajorSubsystemVersion - (DWORD)ImageBase), 16)));

  // MinorSubsystemVersion
  ui->tableWidget->setItem(17,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->MinorSubsystemVersion, 16)));
  ui->tableWidget->setItem(17,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->MinorSubsystemVersion - (DWORD)ImageBase), 16)));

  // Win32VersionValue
  ui->tableWidget->setItem(18,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->Win32VersionValue, 16)));
  ui->tableWidget->setItem(18,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->Win32VersionValue - (DWORD)ImageBase), 16)));

  // SizeOfImage
  ui->tableWidget->setItem(19,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfImage, 16)));
  ui->tableWidget->setItem(19,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfImage - (DWORD)ImageBase), 16)));

  // SizeOfHeaders
  ui->tableWidget->setItem(20,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfHeaders, 16)));
  ui->tableWidget->setItem(20,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfHeaders - (DWORD)ImageBase), 16)));

  // CheckSum
  ui->tableWidget->setItem(21,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->CheckSum, 16)));
  ui->tableWidget->setItem(21,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->CheckSum - (DWORD)ImageBase), 16)));

  // Subsystem
  ui->tableWidget->setItem(22,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->Subsystem, 16)));
  ui->tableWidget->setItem(22,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->Subsystem - (DWORD)ImageBase), 16)));

  // DllCharacteristics
  ui->tableWidget->setItem(23,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->DllCharacteristics, 16)));
  ui->tableWidget->setItem(23,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->DllCharacteristics - (DWORD)ImageBase), 16)));

  // SizeOfStackReserve
  ui->tableWidget->setItem(24,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfStackReserve, 16)));
  ui->tableWidget->setItem(24,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfStackReserve - (DWORD)ImageBase), 16)));

  // SizeOfStackCommit
  ui->tableWidget->setItem(25,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfStackCommit, 16)));
  ui->tableWidget->setItem(25,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfStackCommit - (DWORD)ImageBase), 16)));

  // SizeOfHeapReserve
  ui->tableWidget->setItem(26,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfHeapReserve, 16)));
  ui->tableWidget->setItem(26,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfHeapReserve - (DWORD)ImageBase), 16)));

  // SizeOfHeapCommit
  ui->tableWidget->setItem(27,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->SizeOfHeapCommit, 16)));
  ui->tableWidget->setItem(27,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->SizeOfHeapCommit - (DWORD)ImageBase), 16)));

  // LoaderFlags
  ui->tableWidget->setItem(28,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->LoaderFlags, 16)));
  ui->tableWidget->setItem(28,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->LoaderFlags - (DWORD)ImageBase), 16)));

  // NumberOfRvaAndSizes
  ui->tableWidget->setItem(29,
                           0,
                           new QTableWidgetItem(QString::number(pimage_optional_header->NumberOfRvaAndSizes, 16)));
  ui->tableWidget->setItem(29,
                           1,
                           new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)&pimage_optional_header->NumberOfRvaAndSizes - (DWORD)ImageBase), 16)));

  subSystems[0] = "UNKNOWN";
  subSystems[1] = "NATIVE";
  subSystems[2] = "WINDOWS_GUI";
  subSystems[3] = "WINDOWS_CUI";
  subSystems[5] = "OS2_CUI";
  subSystems[7] = "POSIX_CUI";
  subSystems[8] = "NATIVE_WINDOWS";
  subSystems[9] = "WINDOWS_CE_GUI";
  subSystems[10] = "EFI_APPLICATION";
  subSystems[11] = "EFI_BOOT_SERVICE_DRIVER";
  subSystems[12] = "EFI_RUNTIME_DRIVER";
  subSystems[13] = "EFI_ROM";
  subSystems[14] = "XBOX";
  subSystems[16] = "WINDOWS_BOOT_APPLICATION";
  subSystems[17] = "XBOX_CODE_CATALOG";

  ui->comboBoxSubsystem->setCurrentText(QString::fromStdString(subSystems[pimage_optional_header->Subsystem]));

  // DllCharacteristics checkBox
  QMap<DWORD, QCheckBox*> DllCharacteristics;
  for (int i = 0; i < 16; i++) {
      DllCharacteristics.insert(pow(2, i), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i+1)));
    }
  QMap<DWORD, QCheckBox*>::Iterator iter;
  iter = DllCharacteristics.begin();
  while (iter != DllCharacteristics.end()) {
      if ((pimage_optional_header->DllCharacteristics & iter.key()) != 0) {
          iter.value()->setChecked(true);
        }
      iter++;
    }
}

void FormOptionalHeader::on_comboBoxSubsystem_currentTextChanged(const QString &arg1)
{
    QMap<DWORD, std::string>::Iterator iter;
    iter = subSystems.begin();
    while (iter != subSystems.end()) {
        if (QString::fromStdString(iter.value()) == ui->comboBoxSubsystem->currentText()) {
            ui->tableWidget->setItem(22, 0, new QTableWidgetItem(QString::number(iter.key(), 16)));
            return;;
          }
        iter++;
      }
}

void FormOptionalHeader::checkBox_stateChanged(int arg)
{
  WORD DllCharacteristicsValue = ui->tableWidget->item(23, 0)->text().toInt();
  QMap<DWORD, QCheckBox*> DllCharacteristics;
  for (int i = 0; i < 16; i++) {
      DllCharacteristics.insert(pow(2, i), ui->groupBox->findChild<QCheckBox*>("checkBox_" + QString::number(i+1)));
    }
  QMap<DWORD, QCheckBox*>::Iterator iter;
  iter = DllCharacteristics.begin();
  while (iter != DllCharacteristics.end()) {
      if (iter.value()->isChecked()) {
          DllCharacteristicsValue |= iter.key();
        } else {
          DllCharacteristicsValue &= (~iter.key());
        }
      iter++;
  }
  ui->tableWidget->setItem(23, 0, new QTableWidgetItem(QString::number(DllCharacteristicsValue, 16)));
}

