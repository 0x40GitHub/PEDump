#include "formexporttable.h"
#include "peutils.h"
#include "ui_formexporttable.h"
#include <QDebug>

FormExportTable::FormExportTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormExportTable)
{
  ui->setupUi(this);
}

FormExportTable::~FormExportTable()
{
  delete ui;
}

void FormExportTable::ShowInfo(LPVOID ImageBase)
{
  PIMAGE_DATA_DIRECTORY pimage_data_directory = GetDataDirectory(ImageBase);
  PIMAGE_EXPORT_DIRECTORY pimage_export_directory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)ImageBase + pimage_data_directory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);



   // Characteristics
  ui->tableWidget->setItem(0,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->Characteristics) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(0,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->Characteristics, 8, 16, QLatin1Char('0'))));

  // TimeDateStamp
  ui->tableWidget->setItem(1,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->TimeDateStamp) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(1,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->TimeDateStamp, 8, 16, QLatin1Char('0'))));

  // MajorVersion
  ui->tableWidget->setItem(2,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->MajorVersion) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(2,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->MajorVersion, 4, 16, QLatin1Char('0'))));

  // MinorVersion
  ui->tableWidget->setItem(3,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->MinorVersion) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(3,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->MinorVersion, 4, 16, QLatin1Char('0'))));

  // Name
  ui->tableWidget->setItem(4,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->Name) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(4,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->Name, 8, 16, QLatin1Char('0'))));

  // Base
  ui->tableWidget->setItem(5,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->Base) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(5,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->Base, 8, 16, QLatin1Char('0'))));

  // NumberOfFunctions
  ui->tableWidget->setItem(6,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->NumberOfFunctions) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(6,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->NumberOfFunctions, 8, 16, QLatin1Char('0'))));

  // NumberOfNames
  ui->tableWidget->setItem(7,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->NumberOfNames) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(7,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->NumberOfNames, 8, 16, QLatin1Char('0'))));

  // AddressOfFunctions
  ui->tableWidget->setItem(8,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->AddressOfFunctions) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(8,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->AddressOfFunctions, 8, 16, QLatin1Char('0'))));

  // AddressOfNames
  ui->tableWidget->setItem(9,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->AddressOfNames) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(9,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->AddressOfNames, 8, 16, QLatin1Char('0'))));

  // AddressOfNameOrdinals
  ui->tableWidget->setItem(10,
                           0,
                           new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)&(pimage_export_directory->AddressOfNameOrdinals) - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
  ui->tableWidget->setItem(10,
                           1,
                           new QTableWidgetItem(QString("%1").arg(pimage_export_directory->AddressOfNameOrdinals, 8, 16, QLatin1Char('0'))));
  struct FUNCTION {
    DWORD Ordinal; // 函数导出序号
    DWORD NameOrdinal;
    DWORD FunctionAddr;    // 函数地址
    DWORD NameRVA;        // 函数名称字符串的相对虚拟地址
    std::string FuncName; // 函数名称
  };



  QList<FUNCTION> functions;
  PDWORD Export_Address_Table = (PDWORD)(pimage_export_directory->AddressOfFunctions + (DWORD)ImageBase);
  PWORD Export_Ordinal_Table = (PWORD)(pimage_export_directory->AddressOfNameOrdinals + (DWORD)ImageBase);
  PDWORD Export_Name_Table = (PDWORD)(pimage_export_directory->AddressOfNames + (DWORD)ImageBase);

  QMap<DWORD, DWORD> NameOrdinalToNameRVA;
  for (int i = 0; i < pimage_export_directory->NumberOfNames; i++) {
      NameOrdinalToNameRVA.insert(Export_Ordinal_Table[i], Export_Name_Table[i]);
    }

  for (DWORD i = 0; i < pimage_export_directory->NumberOfFunctions; i++) {
      if (NameOrdinalToNameRVA.count(i)) {
          FUNCTION func = {pimage_export_directory->Base + i,
                           i,
                           Export_Address_Table[i],
                           NameOrdinalToNameRVA[i],
                           (LPCSTR)((DWORD)ImageBase + NameOrdinalToNameRVA[i])};
          functions.append(func);
        } else {
          FUNCTION func = {pimage_export_directory->Base + i,
                           UINT_MAX,
                           Export_Address_Table[i],
                           UINT_MAX,
                           ""};
          functions.append(func);
        }
    }
  QList<FUNCTION>::Iterator iter;
  iter = functions.begin();
  int i = 0;
  while (iter != functions.end()) {
      ui->tableWidget_2->insertRow(i);
      ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(iter->Ordinal, 8, 16, QLatin1Char('0'))));
      ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(iter->FunctionAddr, 8, 16, QLatin1Char('0'))));
      ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(iter->NameOrdinal, 4, 16, QLatin1Char('0'))));
      ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(iter->NameRVA, 8, 16, QLatin1Char('0'))));
      ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(iter->FuncName)));
      iter++;
      i++;
    }

}
