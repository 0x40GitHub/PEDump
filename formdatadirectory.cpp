#include "formdatadirectory.h"
#include "peutils.h"
#include "ui_formdatadirectory.h"
#include "DataDirectory/formexporttable.h"
#include "DataDirectory/formimporttable.h"
#include "DataDirectory/formboundimport.h"
#include "DataDirectory/formresourcetable.h"
#include "DataDirectory/formbaserelocationtable.h"
#include <QDebug>
FormDataDirectory::FormDataDirectory(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormDataDirectory)
{
  ui->setupUi(this);

}

FormDataDirectory::~FormDataDirectory()
{
  delete ui;
}

void FormDataDirectory::ShowInfo(LPVOID ImageBase)
{
  IMAGE_DATA_DIRECTORY* pimage_data_directory = GetDataDirectory(ImageBase);

  for (int i = 0; i < 16; i++) {
      ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(RVAToFOA(ImageBase, (DWORD)pimage_data_directory - (DWORD)ImageBase), 16)));
      ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(pimage_data_directory->VirtualAddress, 16)));
      ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(pimage_data_directory->Size, 16)));
      pimage_data_directory++;
    }
}

// 0导出表
void FormDataDirectory::on_pushButtonExportTable_clicked()
{
    FormExportTable* pform_export_table = new FormExportTable;
    pform_export_table->ShowInfo(this->ImageBase);
    pform_export_table->show();

}

void FormDataDirectory::ReceiveImageBase(LPVOID ImageBase)
{
  this->ImageBase = ImageBase;
}

// 1导入表
void FormDataDirectory::on_pushButtonImportTable_clicked()
{
  FormImportTable* pform_import_table = new FormImportTable;
  pform_import_table->ShowInfo(this->ImageBase);
  pform_import_table->show();
}

// 2异常信息表
void FormDataDirectory::on_pushButton_4_clicked()
{

}
// 3资源表
void FormDataDirectory::on_pushButton_3_clicked()
{
    FormResourceTable* pform_resource_table = new FormResourceTable;
    pform_resource_table->ShowInfo(this->ImageBase);
    pform_resource_table->show();
}

// 4证书属性表
void FormDataDirectory::on_pushButton_5_clicked()
{

}

// 5基址重定位表
void FormDataDirectory::on_pushButton_6_clicked()
{
  FormBaseRelocationTable* pform_base_relocation = new FormBaseRelocationTable;
  pform_base_relocation->ShowInfo(ImageBase);
  pform_base_relocation->show();
}

// 6调试
void FormDataDirectory::on_pushButton_7_clicked()
{

}
// 架构
void FormDataDirectory::on_pushButton_8_clicked()
{

}

// 8全局指针
void FormDataDirectory::on_pushButton_16_clicked()
{

}

// 9线程局部存储
void FormDataDirectory::on_pushButton_9_clicked()
{

}

// 10加载配置信息
void FormDataDirectory::on_pushButton_10_clicked()
{

}
// 11 绑定导入表
void FormDataDirectory::on_pushButton_11_clicked()
{
  FormBoundImport* pform_bound_import = new FormBoundImport;
  pform_bound_import->ShowInfo(this->ImageBase);
  pform_bound_import->show();
}
// 112IAT
void FormDataDirectory::on_pushButton_12_clicked()
{

}

// 13 延迟加载导入表
void FormDataDirectory::on_pushButton_13_clicked()
{

}

// 14 CLR Runtime Header
void FormDataDirectory::on_pushButton_14_clicked()
{

}

