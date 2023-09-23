#include "formbaserelocationtable.h"
#include "peutils.h"
#include "ui_formbaserelocationtable.h"

FormBaseRelocationTable::FormBaseRelocationTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormBaseRelocationTable)
{
  ui->setupUi(this);
}

FormBaseRelocationTable::~FormBaseRelocationTable()
{
  delete ui;
}

void FormBaseRelocationTable::ShowInfo(LPVOID ImageBase)
{


  //1、指向相关内容
  PIMAGE_OPTIONAL_HEADER pOptionalHeader = GetOptionalHeader(ImageBase);

  //2、获取重定位表的地址
  DWORD RelocationDirectory_RAVAdd = pOptionalHeader->DataDirectory[5].VirtualAddress;

  //	(1)、判断重定位表是否存在
  if (RelocationDirectory_RAVAdd == 0)
    {
      printf("RelocationDirectory 不存在!\n");
      return;
    }

  //3、指向重定位表
  PIMAGE_BASE_RELOCATION RelocationDirectory = (PIMAGE_BASE_RELOCATION)((DWORD)ImageBase + RelocationDirectory_RAVAdd);

  //4、循环打印重定位信息  当VirtualAddress和SizeOfBlock都为0时遍历完成
  while (RelocationDirectory->VirtualAddress && RelocationDirectory->SizeOfBlock)
    {
      printf("VirtualAddress    :%08lX\n", RelocationDirectory->VirtualAddress);
      printf("SizeOfBlock       :%08lX\n", RelocationDirectory->SizeOfBlock);
      printf("================= BlockData Start ======================\n");
      ui->plainTextEdit->appendPlainText(QString("VirtualAddress    :%1\n").arg(RelocationDirectory->VirtualAddress, 8, 16, QLatin1Char('0')));
      ui->plainTextEdit->appendPlainText(QString("SizeOfBlock       :%1\n").arg(RelocationDirectory->SizeOfBlock, 8, 16, QLatin1Char('0')));
      ui->plainTextEdit->appendPlainText(QString("================= BlockData Start ======================\n"));
      //5、计算在当前块中的数据个数
      DWORD DataNumber = (RelocationDirectory->SizeOfBlock - 8) / 2;

      //6、指向数据块
      PWORD DataGroup = (PWORD)((DWORD)RelocationDirectory + 8);

      //7、循环打印数据块中的数据
      for (DWORD i = 0; i < DataNumber; i++)
        {
          //(1)判断高4位是否为0
          if (DataGroup[i] >> 12 != 0)
            {
              //(2)提取数据块中的有效数据 低12位
              WORD BlockData = DataGroup[i] & 0xFFF;

              //(3)计算数据块的RVA和FOA
              DWORD Data_RVA = RelocationDirectory->VirtualAddress + BlockData;

              //(4)获取需要重定位的数据
              PDWORD RelocationData = (PDWORD)((DWORD)ImageBase + Data_RVA);

              printf("第[%04lX]项    |数据 :[%04X]   |数据的RVA :[%08lX]  |数据属性 :[%X]  |重定位数据  :[%08lX]\n", i+1, BlockData, Data_RVA, (DataGroup[i] >> 12), *RelocationData);
              ui->plainTextEdit->appendPlainText(QString("第[%1]项    |数据 :[%2]   |数据的RVA :[%3X]  |数据属性 :[%4]  |重定位数据  :[%5]\n").arg(i+1).arg(
                                                   BlockData,
                                                   4,
                                                   16,
                                                   QLatin1Char('0')).arg(
                                                   Data_RVA,
                                                   8,
                                                   16,
                                                   QLatin1Char('0')).arg(
                                                   (DataGroup[i] >> 12),
                                                   8,
                                                   16,
                                                   QLatin1Char('0')).arg(
                                                   *RelocationData,
                                                   8,
                                                   16,
                                                   QLatin1Char('0')));
            }
        }

      printf("================= BlockData End ========================\n");
      ui->plainTextEdit->appendPlainText(QString("================= BlockData End ========================\n"));
      //指向下一个数据块
      RelocationDirectory = (PIMAGE_BASE_RELOCATION)((DWORD)RelocationDirectory + RelocationDirectory->SizeOfBlock);
    }
  return;
}
