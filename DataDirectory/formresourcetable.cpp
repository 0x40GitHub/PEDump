#include "formresourcetable.h"
#include "peutils.h"
#include "ui_formresourcetable.h"
#include <QDebug>

FormResourceTable::FormResourceTable(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormResourceTable)
{
  ui->setupUi(this);
}

FormResourceTable::~FormResourceTable()
{
  delete ui;
}
//资源的类型
int FormResourceTable::ShowInfo(LPVOID ImageBase)
{


  const char* szResType[] = {NULL, "鼠标指针","位图","图标", "菜单", "对话框","字符串","字体目录","字体","加速键","非格式化资源","消息列表","鼠标指针组", NULL,"图标组", NULL,"版本信息"};
   int ret = 0;
  //1、指向相关内容

  PIMAGE_OPTIONAL_HEADER pOptionalHeader = GetOptionalHeader(ImageBase);

  //2、获取资源表的地址
  DWORD ResourceDirectory_RVAAdd = pOptionalHeader->DataDirectory[2].VirtualAddress;

  //	(1)、判断资源表是否存在
  if (ResourceDirectory_RVAAdd == 0)
    {

      return ret;
    }


  //3、指向资源表
  PIMAGE_RESOURCE_DIRECTORY ResourceDirectory = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)ImageBase + ResourceDirectory_RVAAdd);

  //4、打印资源表信息(一级目录)
  printf("|==================================================\n");
  printf("|资源表一级目录信息:\n");
  printf("|Characteristics        :%08lX\n", ResourceDirectory->Characteristics);
  printf("|TimeDateStamp          :%08lX\n", ResourceDirectory->TimeDateStamp);
  printf("|MajorVersion           :%04X\n", ResourceDirectory->MajorVersion);
  printf("|MinorVersion           :%04X\n", ResourceDirectory->MinorVersion);
  printf("|NumberOfNamedEntries   :%04X\n", ResourceDirectory->NumberOfNamedEntries);
  printf("|NumberOfIdEntries      :%04X\n", ResourceDirectory->NumberOfIdEntries);
  printf("|==================================================\n");
  ui->plainTextEdit->appendPlainText(QString("==================================================\n"));
  ui->plainTextEdit->appendPlainText(QString("资源表一级目录信息:\n"));
  ui->plainTextEdit->appendPlainText(QString("Characteristics        :%1\n").arg(ResourceDirectory->Characteristics, 8, 16, QLatin1Char('0')));
  ui->plainTextEdit->appendPlainText(QString("TimeDateStamp          :%1\n").arg(ResourceDirectory->TimeDateStamp, 8, 16, QLatin1Char('0')));
  ui->plainTextEdit->appendPlainText(QString("MajorVersion           :%1\n").arg(ResourceDirectory->MajorVersion, 4, 16, QLatin1Char('0')));
  ui->plainTextEdit->appendPlainText(QString("MinorVersion           :%1\n").arg(ResourceDirectory->MinorVersion, 4, 16, QLatin1Char('0')));
  ui->plainTextEdit->appendPlainText(QString("umberOfNamedEntries    :%1\n").arg(ResourceDirectory->NumberOfNamedEntries, 4, 16, QLatin1Char('0')));
  ui->plainTextEdit->appendPlainText(QString("NumberOfIdEntries      :%1\n").arg(ResourceDirectory->NumberOfIdEntries, 4, 16, QLatin1Char('0')));
  ui->plainTextEdit->appendPlainText(QString("==================================================\n"));

  //4、循环打印后续资源表信息
  //	(1)指向一级目录中的资源目录项(一级目录)	资源类型
  PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)ResourceDirectory + sizeof(IMAGE_RESOURCE_DIRECTORY));
  printf("|----------------------------------------\n");
  ui->plainTextEdit->appendPlainText(QString("----------------------------------------\n"));
  for (int i = 0; i < (ResourceDirectory->NumberOfIdEntries + ResourceDirectory->NumberOfNamedEntries); i++)
    {
      //	(2)判断一级目录中的资源目录项中类型是否是字符串 1 = 字符串(非标准类型)； 0 = 非字符串(标准类型)
      if (ResourceDirectoryEntry->NameIsString)		//字符串(非标准类型)
        {
          //		1.指向名字结构体
          PIMAGE_RESOURCE_DIR_STRING_U pStringName = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)ResourceDirectory + ResourceDirectoryEntry->NameOffset);

          //		2.将Unicode字符串转换成ASCII字符串
          CHAR TypeName[20] = { 0 };
          for (int j = 0; j < pStringName->Length; j++)
            {
              TypeName[j] = (CHAR)pStringName->NameString[j];
            }
          //		3.打印字符串
          printf("|ResourceType           :\"%s\"\n", TypeName);
          ui->plainTextEdit->appendPlainText(QString("ResourceType           :%1\n").arg(TypeName));

        }
      else		//非字符串(标准类型)
        {
          if (ResourceDirectoryEntry->Id < 17)	//只有1 - 16有定义
            {
              printf("|ResourceType           :%s\n", szResType[ResourceDirectoryEntry->Id]);
              ui->plainTextEdit->appendPlainText(QString("ResourceType           :%1\n").arg(QString::fromUtf8(szResType[ResourceDirectoryEntry->Id])));

            }
          else {
              printf("|ResourceType           :%04Xh\n", ResourceDirectoryEntry->Id);
              ui->plainTextEdit->appendPlainText(QString("ResourceType           :%1\n").arg(ResourceDirectoryEntry->Id, 4, 16, QLatin1Char('0')));
            }
        }

      //	(3)判断一级目录中子节点的类型		1 = 目录； 0 = 数据 (一级目录和二级目录该值都为1)
      if (ResourceDirectoryEntry->DataIsDirectory)
        {
          //	(4)打印目录偏移
          printf("OffsetToDirectory      :%08X\n", ResourceDirectoryEntry->OffsetToDirectory);
          printf("----------------------------------------\n");
          ui->plainTextEdit->appendPlainText(QString("OffsetToDirectory      :%1\n").arg(ResourceDirectoryEntry->OffsetToDirectory, 8, 16, QLatin1Char('0')));
          ui->plainTextEdit->appendPlainText(QString("----------------------------------------\n"));
          //	(5)指向二级目录	资源编号
          PIMAGE_RESOURCE_DIRECTORY ResourceDirectory_Sec = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)ResourceDirectory + ResourceDirectoryEntry->OffsetToDirectory);

          //	(6)打印资源表信息(二级目录)
          printf("    |====================================\n");
          printf("    |资源表二级目录信息:\n");
          printf("    |Characteristics        :%08lX\n", ResourceDirectory_Sec->Characteristics);
          printf("    |TimeDateStamp          :%08lX\n", ResourceDirectory_Sec->TimeDateStamp);
          printf("    |MajorVersion           :%04X\n", ResourceDirectory_Sec->MajorVersion);
          printf("    |MinorVersion           :%04X\n", ResourceDirectory_Sec->MinorVersion);
          printf("    |NumberOfNamedEntries   :%04X\n", ResourceDirectory_Sec->NumberOfNamedEntries);
          printf("    |NumberOfIdEntries      :%04X\n", ResourceDirectory_Sec->NumberOfIdEntries);
          printf("    |====================================\n");
          ui->plainTextEdit->appendPlainText(QString("    ====================================\n"));
          ui->plainTextEdit->appendPlainText(QString("    资源表二级目录信息:\n"));
          ui->plainTextEdit->appendPlainText(QString("    Characteristics        :%1\n").arg(ResourceDirectory_Sec->Characteristics, 8, 16, QLatin1Char('0')));
          ui->plainTextEdit->appendPlainText(QString("    TimeDateStamp          :%1\n").arg(ResourceDirectory_Sec->TimeDateStamp, 8, 16, QLatin1Char('0')));
          ui->plainTextEdit->appendPlainText(QString("    MajorVersion           :%1\n").arg(ResourceDirectory_Sec->MajorVersion, 4, 16, QLatin1Char('0')));
          ui->plainTextEdit->appendPlainText(QString("    MinorVersion           :%1\n").arg(ResourceDirectory_Sec->MinorVersion, 4, 16, QLatin1Char('0')));
          ui->plainTextEdit->appendPlainText(QString("    NumberOfNamedEntries   :%1\n").arg(ResourceDirectory_Sec->NumberOfNamedEntries, 4, 16, QLatin1Char('0')));
          ui->plainTextEdit->appendPlainText(QString("    NumberOfIdEntries      :%1\n").arg(ResourceDirectory_Sec->NumberOfIdEntries, 4, 16, QLatin1Char('0')));
          ui->plainTextEdit->appendPlainText(QString("    ====================================\n"));
          //	(7)指向二级目录中的资源目录项
          //	(7)指向二级目录中的资源目录项
          //	(7)指向二级目录中的资源目录项
          //	(7)指向二级目录中的资源目录项
          //	(7)指向二级目录中的资源目录项
          //	(7)指向二级目录中的资源目录项
          PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryEntry_Sec = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)ResourceDirectory_Sec + sizeof(IMAGE_RESOURCE_DIRECTORY));

          //	(8)循环打印二级目录
          for (int j = 0; j < (ResourceDirectory_Sec->NumberOfIdEntries + ResourceDirectory_Sec->NumberOfNamedEntries); j++)
            {
              //	(9)判断二级目录中的资源目录项中编号是否是字符串
              if (ResourceDirectoryEntry_Sec->NameIsString)		//字符串(非标准类型)
                {
                  //		1.指向名字结构体
                  PIMAGE_RESOURCE_DIR_STRING_U pStringName = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)ResourceDirectory + ResourceDirectoryEntry_Sec->NameOffset);

                  //		2.将Unicode字符串转换成ASCII字符串
                  CHAR TypeName[20] = { 0 };
                  for (int k = 0; k < pStringName->Length; k++)
                    {
                      TypeName[k] = (CHAR)pStringName->NameString[k];
                    }
                  //		3.打印字符串
                  printf("    |ResourceNumber         :\"%s\"\n", TypeName);
                  ui->plainTextEdit->appendPlainText(QString("    ResourceNumber         :%1\n").arg(TypeName));
                }
              else		//非字符串(标准类型)
                {
                  printf("    |ResourceNumber         :%04Xh\n", ResourceDirectoryEntry_Sec->Id);
                  ui->plainTextEdit->appendPlainText(QString("    ResourceNumber         :%1\n").arg(ResourceDirectoryEntry_Sec->Id, 4, 16, QLatin1Char('0')));
                }

              //	(10)判断二级目录中子节点的类型
              if (ResourceDirectoryEntry_Sec->DataIsDirectory)
                {
                  //	(11)打印目录偏移
                  printf("    |OffsetToDirectory      :%08X\n", ResourceDirectoryEntry_Sec->OffsetToDirectory);

                  printf("    |------------------------------------\n");
                  ui->plainTextEdit->appendPlainText(QString("    OffsetToDirectory      :%1\n").arg(ResourceDirectoryEntry_Sec->OffsetToDirectory, 8, 16, QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("    ------------------------------------\n"));
                  //	(12)指向三级目录	代码页
                  PIMAGE_RESOURCE_DIRECTORY ResourceDirectory_Thir = (PIMAGE_RESOURCE_DIRECTORY)((DWORD)ResourceDirectory + ResourceDirectoryEntry_Sec->OffsetToDirectory);

                  //	(13)打印资源表信息(三级目录)
                  printf("        |================================\n");
                  printf("        |资源表三级目录信息:\n");
                  printf("        |Characteristics        :%08lX\n", ResourceDirectory_Thir->Characteristics);
                  printf("        |TimeDateStamp          :%08lX\n", ResourceDirectory_Thir->TimeDateStamp);
                  printf("        |MajorVersion           :%04X\n", ResourceDirectory_Thir->MajorVersion);
                  printf("        |MinorVersion           :%04X\n", ResourceDirectory_Thir->MinorVersion);
                  printf("        |NumberOfNamedEntries   :%04X\n", ResourceDirectory_Thir->NumberOfNamedEntries);
                  printf("        |NumberOfIdEntries      :%04X\n", ResourceDirectory_Thir->NumberOfIdEntries);
                  printf("        |================================\n");
                  ui->plainTextEdit->appendPlainText(QString("        ================================\n"));
                  ui->plainTextEdit->appendPlainText(QString("        资源表三级目录信息:\n"));
                  ui->plainTextEdit->appendPlainText(QString("        Characteristics        :%1\n").arg(ResourceDirectory_Thir->Characteristics, 8, 16, QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("        TimeDateStamp          :%1\n").arg(ResourceDirectory_Thir->TimeDateStamp, 8, 16, QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("        MajorVersion           :%1\n").arg(ResourceDirectory_Thir->MajorVersion, 4, 16, QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("        MinorVersion           :%1\n").arg(ResourceDirectory_Thir->MinorVersion, 4, 16, QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("        NumberOfNamedEntries   :%1\n").arg(ResourceDirectory_Thir->NumberOfNamedEntries, 4, 16, QLatin1Char('0')));
                  ui->plainTextEdit->appendPlainText(QString("        NumberOfIdEntries      :%1\n").arg(ResourceDirectory_Thir->NumberOfIdEntries, 4, 16, QLatin1Char('0')));
                  //	(14)指向三级目录中的资源目录项
                  PIMAGE_RESOURCE_DIRECTORY_ENTRY ResourceDirectoryEntry_Thir = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)((DWORD)ResourceDirectory_Thir + sizeof(IMAGE_RESOURCE_DIRECTORY));

                  //	(15)循环打印三级目录项
                  for (int k = 0; k < (ResourceDirectory_Thir->NumberOfNamedEntries + ResourceDirectory_Thir->NumberOfIdEntries); k++)
                    {
                      //	(16)判断三级目录中的资源目录项中编号是否是字符串
                      if (ResourceDirectoryEntry_Thir->NameIsString)		//字符串(非标准类型)
                        {
                          //		1.指向名字结构体
                          PIMAGE_RESOURCE_DIR_STRING_U pStringName = (PIMAGE_RESOURCE_DIR_STRING_U)((DWORD)ResourceDirectory + ResourceDirectoryEntry_Thir->NameOffset);

                          //		2.将Unicode字符串转换成ASCII字符串
                          CHAR TypeName[20] = { 0 };
                          for (int k = 0; k < pStringName->Length; k++)
                            {
                              TypeName[k] = (CHAR)pStringName->NameString[k];
                            }
                          //		3.打印字符串
                          printf("        |CodePageNumber         :\"%s\"\n", TypeName);
                          ui->plainTextEdit->appendPlainText(QString("        CodePageNumber         :%1\n").arg(TypeName));
                        }
                      else		//非字符串(标准类型)
                        {
                          printf("        |CodePageNumber         :%04Xh\n", ResourceDirectoryEntry_Thir->Id);
                          ui->plainTextEdit->appendPlainText(QString("        CodePageNumber         :%1\n").arg(ResourceDirectoryEntry_Thir->Id, 4, 16, QLatin1Char('0')));
                        }

                      //	(17)判断三级目录中子节点的类型		(三级目录子节点都是数据，这里可以省去判断)
                      if (ResourceDirectoryEntry_Thir->DataIsDirectory)
                        {
                          //	(18)打印偏移
                          printf("        |OffsetToDirectory      :%08X\n", ResourceDirectoryEntry_Thir->OffsetToDirectory);

                          printf("        |------------------------------------\n");
                          ui->plainTextEdit->appendPlainText(QString("        OffsetToDirectory      :%1\n").arg(ResourceDirectoryEntry_Thir->OffsetToDirectory, 8, 16, QLatin1Char('0')));
                          ui->plainTextEdit->appendPlainText(QString("        ------------------------------------\n"));
                        }
                      else
                        {
                          //	(18)打印偏移
                          printf("        |OffsetToData           :%08lX\n", ResourceDirectoryEntry_Thir->OffsetToData);
                          printf("        |------------------------------------\n");
                          ui->plainTextEdit->appendPlainText(QString("        OffsetToData           :%1\n").arg(ResourceDirectoryEntry_Thir->OffsetToData, 8, 16, QLatin1Char('0')));
                          ui->plainTextEdit->appendPlainText(QString("        ------------------------------------\n"));
                          //	(19)指向数据内容	(资源表的FOA + OffsetToData)
                          PIMAGE_RESOURCE_DATA_ENTRY ResourceDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)((DWORD)ResourceDirectory + ResourceDirectoryEntry_Thir->OffsetToData);

                          //	(20)打印数据信息
                          printf("            |================================\n");
                          printf("            |资源表的数据信息\n");
                          printf("            |OffsetToData(RVA)      :%08lX\n", ResourceDataEntry->OffsetToData);
                          printf("            |Size                   :%08lX\n", ResourceDataEntry->Size);
                          printf("            |CodePage               :%08lX\n", ResourceDataEntry->CodePage);
                          printf("            |================================\n");
                          ui->plainTextEdit->appendPlainText(QString("            ================================\n"));
                          ui->plainTextEdit->appendPlainText(QString("            资源表的数据信息\n"));
                          ui->plainTextEdit->appendPlainText(QString("            OffsetToData(RVA)      :%1\n").arg(ResourceDataEntry->OffsetToData, 8, 16, QLatin1Char('0')));
                          ui->plainTextEdit->appendPlainText(QString("            Size                   :%1\n").arg(ResourceDataEntry->Size, 8, 16, QLatin1Char('0')));
                          ui->plainTextEdit->appendPlainText(QString("            CodePage               :%1\n").arg(ResourceDataEntry->CodePage, 8, 16, QLatin1Char('0')));
                          ui->plainTextEdit->appendPlainText(QString("            ================================\n"));
                        }

                      ResourceDirectoryEntry_Thir++;
                    }
                }
              //	(21)目录项后移
              ResourceDirectoryEntry_Sec++;
            }

        }
      printf("|----------------------------------------\n");
      ui->plainTextEdit->appendPlainText(QString("----------------------------------------\n"));
      //	(22)目录项后移
      ResourceDirectoryEntry++;
    }

  return ret;
}
