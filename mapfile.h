#ifndef MAPFILE_H
#define MAPFILE_H
#define NOMINMAX
#include <windows.h>
typedef struct _MAP_FILE_STRUCT {
  HANDLE hFile;         // 文件句柄
  HANDLE hMapping;      // 映射文件句柄
  LPVOID ImageBase;     // 映像文件基址(内存对齐)
  LPVOID FileBase;      // 映像文件基地址（文件对齐）
} MAP_FILE_STRUCT;
#endif // MAPFILE_H
