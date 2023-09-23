#include "formboundimport.h"
#include "peutils.h"
#include "ui_formboundimport.h"

FormBoundImport::FormBoundImport(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormBoundImport)
{
  ui->setupUi(this);
}

FormBoundImport::~FormBoundImport()
{
  delete ui;
}

int FormBoundImport::ShowInfo(LPVOID ImageBase)
{


          int ret = 0;
          PIMAGE_OPTIONAL_HEADER pOptionalHeader = GetOptionalHeader(ImageBase);
          // 获取绑定导入表的地址
          DWORD BoundImportDirectory_RVAAdd = pOptionalHeader->DataDirectory[11].VirtualAddress;
          // 判断绑定导入表是否存在
          if (BoundImportDirectory_RVAAdd == 0)
          {
                  return ret;
          }


          // 指向绑定导入表
          PIMAGE_BOUND_IMPORT_DESCRIPTOR BoundImportDirectory = (PIMAGE_BOUND_IMPORT_DESCRIPTOR)((DWORD)ImageBase + BoundImportDirectory_RVAAdd);


          // 获取绑定导入表的基址
          DWORD BaseBoundImport = (DWORD)BoundImportDirectory;

          // 循环打印绑定导入表信息
          while (BoundImportDirectory->OffsetModuleName && BoundImportDirectory->TimeDateStamp)
          {
                  //	1)指向模块名
                  PCHAR pModuleName = (PCHAR)(BaseBoundImport + BoundImportDirectory->OffsetModuleName);

                  //	2)打印绑定导入表信息
//                  printf("ModuleName                  :%s\n", pModuleName);
//                  printf("TimeDateStamp               :%08X\n", BoundImportDirectory->TimeDateStamp);
//                  printf("NumberOfModuleForwarderRefs :%04X\n", BoundImportDirectory->NumberOfModuleForwarderRefs);
//                  printf("================ Start =========================\n");
                  ui->plainTextEdit->appendPlainText(QString("ModuleName                  :%1\n").arg(pModuleName));
                  ui->plainTextEdit->appendPlainText(QString("TimeDateStamp               :%1\n").arg(BoundImportDirectory->TimeDateStamp,8,16,QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("NumberOfModuleForwarderRefs :%1\n").arg(BoundImportDirectory->TimeDateStamp,4,16,QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("================ Start =========================\n"));
                  //	3)循环后续结构
                  for (DWORD i = 0; i < BoundImportDirectory->NumberOfModuleForwarderRefs; i++)
                  {
                          //	4)指向后续结构
                          PIMAGE_BOUND_FORWARDER_REF BoundImport_Ref = (PIMAGE_BOUND_FORWARDER_REF)&BoundImportDirectory[i + 1];//两个结构大小一样

                          //	5)指向模块名
                          pModuleName = (PCHAR)(BaseBoundImport + BoundImport_Ref->OffsetModuleName);

                          //	6)打印信息
//                          printf("ModuleName-----------:%s\n", pModuleName);
//                          printf("TimeDateStamp--------:%08X\n\n", BoundImport_Ref->TimeDateStamp);
                          ui->plainTextEdit->appendPlainText(QString("ModuleName-----------:%1\n").arg(pModuleName));
                          ui->plainTextEdit->appendPlainText(QString("TimeDateStamp               :%1\n").arg(BoundImport_Ref->TimeDateStamp,8,16,QLatin1Char('0')));

                  }
                  //printf("================  End  =========================\n");
                  ui->plainTextEdit->appendPlainText(QString("================  End  =========================\n"));

                  //	7)指向下一个结构
                  BoundImportDirectory = &BoundImportDirectory[BoundImportDirectory->NumberOfModuleForwarderRefs + 1];
          }

          return ret;
}
