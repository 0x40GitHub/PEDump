#include "formfileheader.h"
#include "ui_formfileheader.h"
#include "peutils.h"
#include <QDebug>
#include <QDateTime>

FormFileHeader::FormFileHeader(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormFileHeader)
{


  ui->setupUi(this);
  // Characteristics checkBox
   QList<QCheckBox*> check_box_list;
   for (int i = 1; i <= 16; i++) {
       check_box_list << findChild<QCheckBox*>("checkBox_" + QString::number(i));
     }
   // 手动关联信号和槽函数
  for (int i = 0; i < 16; i++) {
      connect(check_box_list[i], SIGNAL(stateChanged(int)), this, SLOT(checkBox_stateChanged(int)));
    }

}

FormFileHeader::~FormFileHeader()
{
  delete ui;
}
std::map<int, std::string> machines;
void FormFileHeader::ShowInfo(PIMAGE_FILE_HEADER pimage_file_header, LPVOID ImageBase)
{
  char offset[256];
  char value[256];

  sprintf_s(offset, 20, "0x%0.8x", RVAToFOA(ImageBase, (DWORD)pimage_file_header - (DWORD)ImageBase));
  sprintf_s(value, 20, "0x%0.4x", pimage_file_header->Machine);



  machines[IMAGE_FILE_MACHINE_UNKNOWN] = "UNKNOWN";
  machines[IMAGE_FILE_MACHINE_TARGET_HOST] = "HOST";
  machines[IMAGE_FILE_MACHINE_I386] = "I386";
  machines[IMAGE_FILE_MACHINE_R3000] = "R3000";
  machines[IMAGE_FILE_MACHINE_R4000] = "R4000";
  machines[IMAGE_FILE_MACHINE_R10000] = "R10000";
  machines[IMAGE_FILE_MACHINE_WCEMIPSV2] = "WCEMIPSV2";
  machines[IMAGE_FILE_MACHINE_ALPHA] = "ALPHA";
  machines[IMAGE_FILE_MACHINE_SH3] = "SH3";
  machines[IMAGE_FILE_MACHINE_SH3DSP] = "SH3DSP";
  machines[IMAGE_FILE_MACHINE_SH3E] = "SH3E";
  machines[IMAGE_FILE_MACHINE_SH4] = "SH4";
  machines[IMAGE_FILE_MACHINE_SH5] = "SH5";
  machines[IMAGE_FILE_MACHINE_ARM] = "ARM";
  machines[IMAGE_FILE_MACHINE_THUMB] = "THUMB";
  machines[IMAGE_FILE_MACHINE_ARMNT] = "ARMNT";
  machines[IMAGE_FILE_MACHINE_AM33] = "AM33";
  machines[IMAGE_FILE_MACHINE_POWERPC] = "POWERPC";
  machines[IMAGE_FILE_MACHINE_POWERPCFP] = "POWERPCFP";
  machines[IMAGE_FILE_MACHINE_IA64] = "IA64";
  machines[IMAGE_FILE_MACHINE_MIPS16] = "MIPS16";
  machines[IMAGE_FILE_MACHINE_ALPHA64] = "ALPHA64";
  machines[IMAGE_FILE_MACHINE_MIPSFPU] = "MIPSFPU";
  machines[IMAGE_FILE_MACHINE_MIPSFPU16] = "MIPSFPU16";
  machines[IMAGE_FILE_MACHINE_AXP64] = "AXP64";
  machines[IMAGE_FILE_MACHINE_TRICORE] = "TRICORE";
  machines[IMAGE_FILE_MACHINE_CEF] = "CEF";
  machines[IMAGE_FILE_MACHINE_EBC] = "EBC";
  machines[IMAGE_FILE_MACHINE_AMD64] = "AMD64";
  machines[IMAGE_FILE_MACHINE_M32R] = "M32R";
  machines[IMAGE_FILE_MACHINE_ARM64] = "ARM64";
  machines[IMAGE_FILE_MACHINE_CEE] = "CEE";

  ui->labelMachineOffset->setText(offset);
  ui->lineEditMachine->setText(value);

  std::map<int, std::string>::iterator iter;
  iter = machines.begin();
  while (iter != machines.end()) {
      ui->comboBox->addItem(QString::fromStdString(iter->second));
      iter++;
    }
  // default
  ui->comboBox->setCurrentText(QString::fromStdString(machines[pimage_file_header->Machine]));

  // Number Of Sections
  sprintf_s(offset, 20, "%0.8x", RVAToFOA(ImageBase, (DWORD)&pimage_file_header->NumberOfSections - (DWORD)ImageBase));
  sprintf_s(value, 20, "%0.4x", pimage_file_header->NumberOfSections);
  ui->labelNumberOfSectionsOffset->setText(offset);
  ui->lineEditNumberOfSections->setText(value);

  // TimeDateStamp
  sprintf_s(offset, 20, "%0.8x", RVAToFOA(ImageBase, (DWORD)&pimage_file_header->TimeDateStamp - (DWORD)ImageBase));
  sprintf_s(value, 20, "%0.8x", pimage_file_header->TimeDateStamp);
  ui->labelTimeDateStampOffset->setText(offset);
  ui->lineEditTimeDateStamp->setText(value);

  // TimeDateStampHuman
  ui->lineEditTimeDateStampHuman->setText(QDateTime::fromTime_t(pimage_file_header->TimeDateStamp).toString("yyyy/MM/dd hh:mm:ss"));

  // PointerToSymbolTable
  sprintf_s(offset, 20, "%0.8x", RVAToFOA(ImageBase, (DWORD)&pimage_file_header->PointerToSymbolTable - (DWORD)ImageBase));
  sprintf_s(value, 20, "%0.8x", pimage_file_header->PointerToSymbolTable);
  ui->labelPointerToSymbolTableOffset->setText(offset);
  ui->lineEditPointerToSymbolTable->setText(value);

  // NumberOfSymbols
   sprintf_s(offset, 20, "%0.8x", RVAToFOA(ImageBase, (DWORD)&pimage_file_header->NumberOfSymbols - (DWORD)ImageBase));
   ui->labelNumberOfSymbolsOffset->setText(offset);
   ui->lineEditNumberOfSymbols->setText(QString::number(pimage_file_header->NumberOfSymbols));

  // SizeOfOptionalHeader
   sprintf_s(offset, 20, "%0.8x", RVAToFOA(ImageBase, (DWORD)&pimage_file_header->SizeOfOptionalHeader - (DWORD)ImageBase));
   sprintf_s(value, 20, "%0.4x", pimage_file_header->SizeOfOptionalHeader);
   ui->labelSizeOfOptionalHeaderOffset->setText(offset);
   ui->lineEditSizeOfOptionalHeader->setText(value);
  // Characteristics
   sprintf_s(offset, 20, "%0.8x", RVAToFOA(ImageBase, (DWORD)&pimage_file_header->Characteristics - (DWORD)ImageBase));
   sprintf_s(value, 20, "%0.4x", pimage_file_header->Characteristics);
   ui->labelCharacteristicsOffset->setText(offset);
   ui->lineEditCharacteristics->setText(value);

  // Characteristics checkBox
   QList<QCheckBox*> check_box_list;
   for (int i = 1; i <= 16; i++) {
       check_box_list << findChild<QCheckBox*>("checkBox_" + QString::number(i));
     }
   QList<WORD> characteristcs;
   for (WORD i = 0;i < 16; i++) {
       characteristcs.append(pow(2,i));
     }

   for (int i = 0; i < 16; i++) {
       if ((pimage_file_header->Characteristics & characteristcs[i]) != 0) {
           check_box_list[i]->setChecked(true);
         }
     }


}

void FormFileHeader::on_comboBox_currentTextChanged(const QString &arg1)
{
  char machine[256];
  std::map<int, std::string>::iterator iter;
  iter = machines.begin();
  while (iter != machines.end()) {
      if (iter->second == arg1.toStdString()){
          sprintf_s(machine, 20, "%0.4x", iter->first);
          ui->lineEditMachine->setText(machine);
          return;
        }
      iter++;
    }
}


void FormFileHeader::checkBox_stateChanged(int checked)
{
  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(ImageBase);
  WORD newCharacteristics = pimage_file_header->Characteristics;

  // Characteristics checkBox
   QList<QCheckBox*> check_box_list;
   for (int i = 1; i <= 16; i++) {
       check_box_list << findChild<QCheckBox*>("checkBox_" + QString::number(i));
     }
   QList<WORD> characteristcs;
   for (WORD i = 0;i < 16; i++) {
       characteristcs.append(pow(2,i));
     }

   for (int i = 0; i < 16; i++) {
       if (check_box_list[i]->isChecked()) {
           newCharacteristics |= characteristcs[i];
         }else {
           newCharacteristics &= (~characteristcs[i]);
         }
     }
   char value[256];
   sprintf_s(value, 20, "%0.4x", newCharacteristics);
   ui->lineEditCharacteristics->setText(value);
}

