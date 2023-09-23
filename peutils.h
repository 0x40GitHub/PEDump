#ifndef PEUTILS_H
#define PEUTILS_H
#include <windows.h>
#include <winnt.h>
#include <QByteArray>
// file offset address (FOA)
DWORD RVAToFOA(LPVOID ImageBase, DWORD RVA);

DWORD FOAToRVA(LPVOID ImageBase, DWORD FOA);

// check pe file format
bool IsPEFile(LPVOID ImageBase);

// MS-DOS Header
PIMAGE_DOS_HEADER GetMSDOSHeader(LPVOID ImageBase);

// NT Headers
PIMAGE_NT_HEADERS GetNTHeaders(LPVOID ImageBase);

// File Header
PIMAGE_FILE_HEADER GetFileHeader(LPVOID ImageBase);

// Optional header
PIMAGE_OPTIONAL_HEADER GetOptionalHeader(LPVOID ImageBase);

// First Section Header
PIMAGE_SECTION_HEADER GetFirstSectionHeader(LPVOID ImageBase);

// DataDirectory
IMAGE_DATA_DIRECTORY* GetDataDirectory(LPVOID ImageBase);

// 根据函数名称找函数的rva
DWORD GetFuncRVA(LPVOID ImageBase, LPCSTR _FuncName);

// 根据函数序号找函数的rva
DWORD GetFuncRVA(LPVOID ImageBase, UINT Ordinal);

// 将PE文件的内存映像压缩
DWORD ImageBufferToFileBuffer(LPVOID PImageBuffer, LPVOID& PFileBuffer);

// 添加一个节
LPVOID AddSection(LPVOID PImageBuffer, DWORD SizeOfRawData);

DWORD GetAlignment(IN DWORD X, IN DWORD alignment);

// 扩大一个节
LPVOID ExpandSection(LPVOID PImageBuffer, DWORD Increment);

// 合并所有节
LPVOID MergeSection(LPVOID PImageBuffer);

// Get Image
char* GetImage(LPVOID ImageBase);
#endif // PEUTILS_H
