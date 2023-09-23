#include<windows.h>
#include<winnt.h>
#include "peutils.h"
#include <QMessageBox>
char keybuffer[MAX_PATH];


void XOR(char* soure, int dLen, char* Key, int Klen)
{
    for (int i = 0; i < dLen;)
    {
        for (int j = 0; (j < Klen) && (i < dLen); j++, i++)
        {
            soure[i] = soure[i] ^ Key[j];
            soure[i] = ~soure[i];
        }
    }
        for (int i = 0; i < dLen; i++)
        {
                char m = soure[i];
                soure[i] = soure[dLen - i - 1];
                soure[dLen - i - 1] = m;
        }
}

void SMC_De(char* pBuf, char* key)     //SMC解密函数
{
	const char* szSecName = ".SMC";
	short nSec;
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeader;
	PIMAGE_SECTION_HEADER pSec;
	pDosHeader = (PIMAGE_DOS_HEADER)pBuf;
	pNtHeader = (PIMAGE_NT_HEADERS)&pBuf[pDosHeader->e_lfanew];
	nSec = pNtHeader->FileHeader.NumberOfSections;
	pSec = (PIMAGE_SECTION_HEADER)&pBuf[sizeof(IMAGE_NT_HEADERS) + pDosHeader->e_lfanew];
	for (int i = 0; i < nSec; i++)
	{
		if (strcmp((char*)&pSec->Name, szSecName) == 0)
		{
			int pack_size;
			char* packStart;
			pack_size = pSec->SizeOfRawData;
			packStart = &pBuf[pSec->VirtualAddress];
			XOR(packStart, pack_size, key, strlen(key));
			return;
		}
		pSec++;
	}
}



void UnPack(char* Key)   //解密函数
{
	char* hMod;
	hMod = (char*)GetModuleHandle(0);  //获得当前的exe模块地址
	SMC_De(hMod, Key);
}

void check(char *strc)
{
	UnPack(strc);  //解密
//	__try
//	{
//		;
//	}
//	__except (1)
//	{
//		UnPack(strc); //修正数据
//		QMessageBox::warning(NULL, "密码错误，被加密了！",  QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//		goto label;
//	}
	//UnPack(strc);  //复原
}
