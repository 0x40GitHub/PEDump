#include "formimporttable.h"
#include "peutils.h"
#include "ui_formimporttable.h"
#include <QDebug>
#include <QStandardItemModel>
FormImportTable::FormImportTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormImportTable)
{
  ui->setupUi(this);
}

FormImportTable::~FormImportTable()
{
  delete ui;
}

void FormImportTable::ShowInfo(LPVOID ImageBase)
{ this->ImageBase = ImageBase;
  PIMAGE_DATA_DIRECTORY pimage_data_directory = GetDataDirectory(ImageBase);
  PIMAGE_IMPORT_DESCRIPTOR pimage_import_descriptor = (PIMAGE_IMPORT_DESCRIPTOR) ((DWORD)ImageBase + pimage_data_directory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

  QMap<DWORD, PIMAGE_IMPORT_DESCRIPTOR> IID;
  DWORD index = 0;
  while (pimage_import_descriptor->Characteristics) {
      IID.insert(index++, pimage_import_descriptor);
      pimage_import_descriptor++;
    }
  QMap<DWORD, PIMAGE_IMPORT_DESCRIPTOR>::Iterator iter;
  iter = IID.begin();
  while (iter != IID.end()) {
      ui->tableWidget->insertRow(iter.key());
      // Offset
      ui->tableWidget->setItem(iter.key(),
                               0,
                               new QTableWidgetItem(QString("%1").arg(RVAToFOA(ImageBase, (DWORD)iter.value() - (DWORD)ImageBase), 8, 16, QLatin1Char('0'))));
      // OriginalFirstThunk
      ui->tableWidget->setItem(iter.key(),
                               1,
                               new QTableWidgetItem(QString("%1").arg(iter.value()->OriginalFirstThunk, 8, 16, QLatin1Char('0'))));
      // TimeDateStamp
      ui->tableWidget->setItem(iter.key(),
                               2,
                               new QTableWidgetItem(QString("%1").arg(iter.value()->TimeDateStamp, 8, 16, QLatin1Char('0'))));
      // ForwarderChain
      ui->tableWidget->setItem(iter.key(),
                               3,
                               new QTableWidgetItem(QString("%1").arg(iter.value()->ForwarderChain, 8, 16, QLatin1Char('0'))));
      // Name
      ui->tableWidget->setItem(iter.key(),
                               4,
                               new QTableWidgetItem(QString::fromStdString((LPCSTR)((DWORD)ImageBase + iter.value()->Name))));
      //  FirstThunk
      ui->tableWidget->setItem(iter.key(),
                               5,
                               new QTableWidgetItem(QString("%1").arg(iter.value()->FirstThunk, 8, 16, QLatin1Char('0'))));
      iter++;
    }
}

void FormImportTable::on_tableWidget_itemClicked(QTableWidgetItem *item)
{

  QStringList strs = {"IMAGE_THUNK_DATA32", "Ordinal", "Name", "Hint"};
  QStandardItemModel* model = new QStandardItemModel();
  QStandardItemModel* model2 = new QStandardItemModel();
  model->setHorizontalHeaderLabels(strs);
  model2->setHorizontalHeaderLabels(strs);

  PIMAGE_DATA_DIRECTORY pimage_data_directory = GetDataDirectory(ImageBase);
  PIMAGE_IMPORT_DESCRIPTOR pimage_import_descriptor = (PIMAGE_IMPORT_DESCRIPTOR) ((DWORD)ImageBase + pimage_data_directory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

  QMap<DWORD, PIMAGE_IMPORT_DESCRIPTOR> IID;
  DWORD index = 0;
  while (pimage_import_descriptor->Characteristics) {
      IID.insert(index++, pimage_import_descriptor);
      pimage_import_descriptor++;
    }

  DWORD i = item->row();

  // INT
  int c1 = 0;
  PDWORD OriginalThunk = (PDWORD)(IID[i]->OriginalFirstThunk + (DWORD)ImageBase);
  while (*OriginalThunk) {
      DWORD Ordinal = NULL;
      WORD Hint = NULL;
      LPCSTR Name = "";
      if ((*OriginalThunk & 0x80000000) != 0) {
          Ordinal = *OriginalThunk & 0x7fffffff;
        } else {
          PIMAGE_IMPORT_BY_NAME pimage_import_by_name = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImageBase + *OriginalThunk);
          Hint = pimage_import_by_name->Hint;
          Name = (pimage_import_by_name->Name);
        }

      model->setItem(c1, 0, new QStandardItem(QString("%1").arg(*OriginalThunk, 8, 16, QLatin1Char('0'))));
      model->setItem(c1, 1, new QStandardItem(QString::number(Ordinal)));
      model->setItem(c1, 2, new QStandardItem(QString::fromStdString(Name)));
      model->setItem(c1, 3, new QStandardItem(QString::number(Hint)));
      c1++;
      OriginalThunk++;
    }
  ui->tableView_INT->setModel(model);

  // IAT
  int c2 = 0;
  PDWORD FirstThunk = (PDWORD)(IID[i]->FirstThunk + (DWORD)ImageBase);
  while (*FirstThunk) {
      if (IID[i]->TimeDateStamp != -1) {
          DWORD Ordinal = NULL;
          WORD Hint = NULL;
          LPCSTR Name = "";

          if ((*FirstThunk & 0x80000000) != 0) {
              Ordinal = *FirstThunk & 0x7fffffff;
            } else {
              PIMAGE_IMPORT_BY_NAME pimage_import_by_name = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImageBase + *FirstThunk);
              Hint = pimage_import_by_name->Hint;
              Name = (pimage_import_by_name->Name);
            }
          model2->setItem(c2, 0, new QStandardItem(QString("%1").arg(*FirstThunk, 8, 16, QLatin1Char('0'))));
          model2->setItem(c2, 1, new QStandardItem(QString::number(Ordinal)));
          model2->setItem(c2, 2, new QStandardItem(QString::fromStdString(Name)));
          model2->setItem(c2, 3, new QStandardItem(QString::number(Hint)));
        }
      if (IID[i]->TimeDateStamp == -1) {
          model2->setItem(c2, 0, new QStandardItem(QString("%1").arg(*FirstThunk, 8, 16, QLatin1Char('0'))));
        }

      c2++;
      FirstThunk++;
    }
  ui->tableView_IAT->setModel(model2);
}
