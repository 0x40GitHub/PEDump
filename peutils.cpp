#include "peutils.h"

#include <QDebug>

#pragma code_seg(".SMC")

// file offset address to relative virtual address
DWORD RVAToFOA(LPVOID ImageBase, DWORD RVA)
{

  PIMAGE_OPTIONAL_HEADER pimage_optional_header = nullptr;
  PIMAGE_SECTION_HEADER pimage_section_headers = nullptr;
  PIMAGE_FILE_HEADER pimage_file_header = nullptr;
  DWORD number_of_sections = 0;
  // offset from the section's base address
  DWORD offset_in_section = 0;
  // address from the file base address(0)
  DWORD file_offset_address;

  pimage_optional_header = GetOptionalHeader(ImageBase);
  pimage_section_headers = GetFirstSectionHeader(ImageBase);
  pimage_file_header = GetFileHeader(ImageBase);
  number_of_sections = pimage_file_header->NumberOfSections;

  // if the RVA is in headers(MS-DOS Header, NT Headers, Section Headers)
  if (RVA < pimage_optional_header->SizeOfHeaders) {
      return RVA;
    }
  // if the RVA is in a section
  for (DWORD i = 0; i < number_of_sections; i++) {
      if (pimage_section_headers->VirtualAddress <= RVA && RVA < pimage_section_headers->VirtualAddress + pimage_section_headers->SizeOfRawData) {
          offset_in_section = RVA - pimage_section_headers->VirtualAddress;
          file_offset_address = pimage_section_headers->PointerToRawData + offset_in_section;
          return file_offset_address;
        }
      pimage_section_headers++;
    }
  return 0;
}
#pragma code_seg()
#pragma comment(linker, "/SECTION:.SMC,ERW")


// 判断是否PE文件
bool IsPEFile(LPVOID ImageBase)
{
  PIMAGE_DOS_HEADER pimage_dos_header = nullptr;
  PIMAGE_NT_HEADERS pimage_nt_headers = nullptr;

  if (!ImageBase) {
      return false;
    }
  // 判断MS-DOS 头的"MZ"标志
  pimage_dos_header = (PIMAGE_DOS_HEADER) ImageBase;
  if (pimage_dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
      return false;
    }
  // 判断PE文件头的"PE00"标志
  pimage_nt_headers = (PIMAGE_NT_HEADERS) ((DWORD)ImageBase + pimage_dos_header->e_lfanew);
  if (pimage_nt_headers->Signature != IMAGE_NT_SIGNATURE) {
      return false;
    }
  return true;
}

// get MS-DOS Header
PIMAGE_DOS_HEADER GetMSDOSHeader(LPVOID ImageBase) {
  PIMAGE_DOS_HEADER pimage_dos_header = nullptr;
  if (!IsPEFile(ImageBase)) {
      return nullptr;
    }
  pimage_dos_header = (PIMAGE_DOS_HEADER)ImageBase;
  return pimage_dos_header;
}

// get NT Headers
PIMAGE_NT_HEADERS GetNTHeaders(LPVOID ImageBase)
{
  PIMAGE_NT_HEADERS pimage_nt_headers = nullptr;
  PIMAGE_DOS_HEADER pimage_dos_header = nullptr;
  if (!IsPEFile(ImageBase)) {
      return nullptr;
    }
  pimage_dos_header = (PIMAGE_DOS_HEADER)ImageBase;
  pimage_nt_headers = (PIMAGE_NT_HEADERS)((DWORD)pimage_dos_header + pimage_dos_header->e_lfanew);
  return pimage_nt_headers;
}

// get File Header
PIMAGE_FILE_HEADER GetFileHeader(LPVOID ImageBase)
{
  PIMAGE_NT_HEADERS pimage_nt_headers = nullptr;
  PIMAGE_FILE_HEADER pimage_file_header = nullptr;
  pimage_nt_headers = GetNTHeaders(ImageBase);
  if (!pimage_nt_headers) {
      return nullptr;
    }
  pimage_file_header = &(pimage_nt_headers->FileHeader);
  return pimage_file_header;

}

// get Optional Header
PIMAGE_OPTIONAL_HEADER GetOptionalHeader(LPVOID ImageBase)
{
  PIMAGE_NT_HEADERS pimage_nt_headers = nullptr;
  PIMAGE_OPTIONAL_HEADER pimage_optional_header = nullptr;
  pimage_nt_headers = GetNTHeaders(ImageBase);
  if (!pimage_nt_headers) {
      return nullptr;
    }
  pimage_optional_header = &(pimage_nt_headers->OptionalHeader);
  return pimage_optional_header;
}

// get First Section Header
PIMAGE_SECTION_HEADER GetFirstSectionHeader(LPVOID ImageBase)
{
  PIMAGE_OPTIONAL_HEADER pimage_optional_header = nullptr;
  PIMAGE_SECTION_HEADER pimage_first_section_header = nullptr;
  PIMAGE_FILE_HEADER pimage_file_header = nullptr;
  pimage_optional_header = GetOptionalHeader(ImageBase);
  pimage_file_header = GetFileHeader(ImageBase);
  if (!pimage_optional_header || !pimage_file_header) {
      return nullptr;
    }
  pimage_first_section_header = (PIMAGE_SECTION_HEADER)((DWORD)pimage_optional_header + pimage_file_header->SizeOfOptionalHeader);
  return pimage_first_section_header;
}
// get DataDirectory
IMAGE_DATA_DIRECTORY *GetDataDirectory(LPVOID ImageBase)
{
  PIMAGE_OPTIONAL_HEADER pimage_optional_header = GetOptionalHeader(ImageBase);
  if (!pimage_optional_header) {
      return nullptr;
    }
  IMAGE_DATA_DIRECTORY* pimage_data_directory = pimage_optional_header->DataDirectory;
  return pimage_data_directory;
}





// 根据函数名称获取函数地址
DWORD GetFuncRVA(LPVOID ImageBase, LPCSTR _FuncName) {

  PIMAGE_DATA_DIRECTORY pimage_data_directory = GetDataDirectory(ImageBase);
  PIMAGE_EXPORT_DIRECTORY pimage_export_directory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)ImageBase + pimage_data_directory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
  DWORD FunctionRVA = NULL;

  // 搜索函数名称表 Export Name Table
  LPCSTR FunctionName;
  DWORD i = 0;
  PDWORD Export_Name_Table = (PDWORD)(pimage_export_directory->AddressOfNames + (DWORD)ImageBase);
  for (DWORD i = 0; i < pimage_export_directory->NumberOfNames; i++) {
      FunctionName = (LPCSTR)(*Export_Name_Table + (DWORD)ImageBase);
      if (strcmp(FunctionName, _FuncName)) {
          break;
        }
      Export_Name_Table++;
    }
  // 根据索引到Export Ordinal Table中寻找
  PWORD Export_Ordinal_Table = (PWORD)(pimage_export_directory->AddressOfNameOrdinals + (DWORD)ImageBase);
  UINT NameOrdinal = Export_Ordinal_Table[i];
  // 根据索引到Export Address Tabl中寻找
  PDWORD Export_Address_Tabl = (PDWORD)(pimage_export_directory->AddressOfFunctions + (DWORD)ImageBase);
  FunctionRVA = Export_Address_Tabl[NameOrdinal];
  return FunctionRVA;
}

// 根据函数导出序号获取函数地址
DWORD GetFuncRVA(LPVOID ImageBase, UINT Ordinal) {
  PIMAGE_DATA_DIRECTORY pimage_data_directory = GetDataDirectory(ImageBase);
  PIMAGE_EXPORT_DIRECTORY pimage_export_directory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)ImageBase + pimage_data_directory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
  DWORD FunctionRVA = NULL;

  UINT NameOrdinal = Ordinal - pimage_export_directory->Base;
  // 根据索引到Export Address Tabl中寻找
  PDWORD Export_Address_Tabl = (PDWORD)(pimage_export_directory->AddressOfFunctions + (DWORD)ImageBase);
  FunctionRVA = Export_Address_Tabl[NameOrdinal];
  return FunctionRVA;

}
// 将文件压缩
DWORD ImageBufferToFileBuffer(LPVOID PImageBuffer, LPVOID& PFileBuffer)
{

  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(PImageBuffer);
  PIMAGE_OPTIONAL_HEADER pimage_optional_header = GetOptionalHeader(PImageBuffer);
  PIMAGE_SECTION_HEADER pimage_section_header = GetFirstSectionHeader(PImageBuffer);
  // PE文件头:MS-DOS Header, NT Headers, File Header, OPtional Header, Section Header所占空间（按照文件对齐）
  DWORD SizeOfHeaders = pimage_optional_header->SizeOfHeaders;
  DWORD SizeOfFileBuffer = 0;
  DWORD NumberOfSections = pimage_file_header->NumberOfSections;

  // 计算文件映像的大小
  PIMAGE_SECTION_HEADER End_Section;
  End_Section = pimage_section_header + (NumberOfSections - 1);

  SizeOfFileBuffer = End_Section->PointerToRawData + End_Section->SizeOfRawData;
  // 分配空间
  PFileBuffer = (LPVOID)malloc(SizeOfFileBuffer);
  if (!PFileBuffer) {
      return 0;
    }

  memset(PFileBuffer, 0, SizeOfFileBuffer);
  // 拷贝表头
  memcpy_s(PFileBuffer, SizeOfHeaders, PImageBuffer, SizeOfHeaders);

  BYTE* SectionFileAddr;
  BYTE* SectionVisualAddr;
  DWORD SectionSize;
  for (DWORD i = 0; i < NumberOfSections; i++) {
      SectionFileAddr = pimage_section_header->PointerToRawData + (BYTE*)PFileBuffer;
      SectionVisualAddr = pimage_section_header->VirtualAddress + (BYTE*)PImageBuffer;
      SectionSize = pimage_section_header->SizeOfRawData;
      // 写入节数据
      memcpy_s(SectionFileAddr, SectionSize, SectionVisualAddr, SectionSize);
      pimage_section_header++;
    }
  return SizeOfFileBuffer;
}

LPVOID AddSection(LPVOID PImageBuffer, DWORD SizeOfRawData)
{

  PIMAGE_OPTIONAL_HEADER pimage_optional_header = GetOptionalHeader(PImageBuffer);
  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(PImageBuffer);
  PIMAGE_SECTION_HEADER pimage_section_header = GetFirstSectionHeader(PImageBuffer);

  // 添加节后的文件映像大小(内存对齐)
  DWORD NewSizeOfImage = pimage_optional_header->SizeOfImage + GetAlignment(SizeOfRawData, pimage_optional_header->SectionAlignment);
  LPVOID NewPImageBuffer = nullptr;
  NewPImageBuffer = malloc(NewSizeOfImage);
  if (!NewPImageBuffer) {
      return 0;
    }
  memset(NewPImageBuffer, 0, NewSizeOfImage);

  // 拷贝原数据
  memcpy_s(NewPImageBuffer, pimage_optional_header->SizeOfImage, PImageBuffer, pimage_optional_header->SizeOfImage);

  // 新的PE文件映像
  pimage_file_header = GetFileHeader(NewPImageBuffer);
  pimage_optional_header = GetOptionalHeader(NewPImageBuffer);
  pimage_section_header = GetFirstSectionHeader(NewPImageBuffer);




  // 新添加的节的节表的相对虚拟地址
  DWORD NumberOfSections = pimage_file_header->NumberOfSections;
  pimage_section_header = GetFirstSectionHeader(NewPImageBuffer);

  PIMAGE_SECTION_HEADER LastSection = pimage_section_header + (NumberOfSections - 1);
  PIMAGE_SECTION_HEADER NewSectionHeader = pimage_section_header + NumberOfSections;
  for (DWORD i = 0; i < NumberOfSections; i++) {
      if (pimage_section_header->Characteristics == (IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE)) {
          break;
        }
      pimage_section_header++;
    }
  memcpy_s(NewSectionHeader, IMAGE_SIZEOF_SECTION_HEADER, pimage_section_header, IMAGE_SIZEOF_SECTION_HEADER);




  // 计算新添加的节的相对虚拟地址，按照内存对齐值
  DWORD NewSectionRVA = 0;
  NewSectionRVA = LastSection->VirtualAddress + GetAlignment(LastSection->Misc.VirtualSize, pimage_optional_header->SectionAlignment);

  // 修改节属性
  NewSectionHeader->VirtualAddress = NewSectionRVA;
  NewSectionHeader->SizeOfRawData = GetAlignment(SizeOfRawData, pimage_optional_header->FileAlignment);
  NewSectionHeader->Misc.VirtualSize = NewSectionHeader->SizeOfRawData;



  // 计算新添加的节的文件偏移地址
  DWORD NewSectionFileOffset = 0;
  NewSectionFileOffset = LastSection->PointerToRawData + LastSection->SizeOfRawData;

  NewSectionHeader->PointerToRawData = NewSectionFileOffset;


  pimage_file_header->NumberOfSections += 1;
  pimage_optional_header->SizeOfImage = NewSizeOfImage;


  return NewPImageBuffer;
}
// x按照对齐值需要占据的大小
DWORD GetAlignment(DWORD X, DWORD alignment)
{
  if (X % alignment == 0) {
      return X;
    }
  else {
      return (X / alignment + 1) * alignment;
    }
}

LPVOID ExpandSection(LPVOID PImageBuffer, DWORD Increment)
{
  PIMAGE_OPTIONAL_HEADER pimage_optional_header= GetOptionalHeader(PImageBuffer);
  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(PImageBuffer);
  PIMAGE_SECTION_HEADER pimage_section_header = GetFirstSectionHeader(PImageBuffer);

  DWORD SizeOfImage = pimage_optional_header->SizeOfImage;


  LPVOID PNewImageBuffer = malloc(pimage_optional_header->SizeOfImage + GetAlignment(Increment, pimage_optional_header->SectionAlignment));
  if (!PNewImageBuffer) {
      return 0;
    }
  memset(PNewImageBuffer, 0, pimage_optional_header->SizeOfImage + GetAlignment(Increment, pimage_optional_header->SectionAlignment));
  memcpy_s(PNewImageBuffer, SizeOfImage, PImageBuffer, SizeOfImage);

  pimage_optional_header= GetOptionalHeader(PNewImageBuffer);
  pimage_file_header = GetFileHeader(PNewImageBuffer);
  pimage_section_header = GetFirstSectionHeader(PNewImageBuffer);
  PIMAGE_SECTION_HEADER End_Section;
  DWORD NumberOfSections = pimage_file_header->NumberOfSections;
  End_Section = pimage_section_header + (NumberOfSections - 1);

  End_Section->Misc.VirtualSize += GetAlignment(Increment, pimage_optional_header->SectionAlignment);
  End_Section->SizeOfRawData += GetAlignment(Increment, pimage_optional_header->FileAlignment);
  pimage_optional_header->SizeOfImage += GetAlignment(Increment, pimage_optional_header->SectionAlignment);

  return PNewImageBuffer;
}

LPVOID MergeSection(LPVOID PImageBuffer)
{

  LPVOID PNewImageBuffer = nullptr;
  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(PImageBuffer);

  PIMAGE_OPTIONAL_HEADER pimage_optional_header = GetOptionalHeader(PImageBuffer);

  PIMAGE_SECTION_HEADER pimage_section_header = GetFirstSectionHeader(PImageBuffer);

  PNewImageBuffer = malloc(pimage_optional_header->SizeOfImage);

  memcpy_s(PNewImageBuffer, pimage_optional_header->SizeOfImage, PImageBuffer, pimage_optional_header->SizeOfImage);

  pimage_file_header = GetFileHeader(PNewImageBuffer);

  pimage_optional_header = GetOptionalHeader(PNewImageBuffer);

  pimage_section_header = GetFirstSectionHeader(PNewImageBuffer);

  DWORD SizeOfSection = pimage_optional_header->SizeOfImage - pimage_section_header->VirtualAddress;
  pimage_section_header->Misc.VirtualSize = pimage_section_header->SizeOfRawData = SizeOfSection;
  // 修改节属性
  for (int i = 1; i <= pimage_file_header->NumberOfSections; i++) {
      pimage_section_header->Characteristics = pimage_section_header->Characteristics | ((pimage_section_header + i)->Characteristics);// 合并所有节的属性
    }
  // 修改节数量
  pimage_file_header->NumberOfSections = 1;
  return PNewImageBuffer;
}

char* GetImage(LPVOID ImageBase)
{

  PIMAGE_OPTIONAL_HEADER pimage_optioanl_header = GetOptionalHeader(ImageBase);
  char* ImageByteArray = new char[pimage_optioanl_header->SizeOfImage];
  memcpy_s(ImageByteArray, pimage_optioanl_header->SizeOfImage, ImageBase, pimage_optioanl_header->SizeOfImage);
  return ImageByteArray;
}
// 文件偏移地址转相对虚拟地址
DWORD FOAToRVA(LPVOID ImageBase, DWORD FOA)
{
  PIMAGE_OPTIONAL_HEADER pimage_optioanl_header = GetOptionalHeader(ImageBase);
  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(ImageBase);
  PIMAGE_SECTION_HEADER pimage_section_header = GetFirstSectionHeader(ImageBase);

  if (FOA < pimage_optioanl_header->SizeOfHeaders) {
      return FOA;
    }


  DWORD NumberOfSections = pimage_file_header->NumberOfSections;
  // 偏移地址在节中的偏移
  DWORD OffsetINSection = 0;
  // 偏移地址在内存中的偏移
  DWORD RVA = 0;
  for (DWORD i = 0; i < NumberOfSections; i++) {
      if (pimage_section_header->PointerToRawData <= FOA && FOA < pimage_section_header->PointerToRawData + pimage_section_header->SizeOfRawData) {
          OffsetINSection = FOA - pimage_section_header->PointerToRawData;
          RVA = pimage_section_header->VirtualAddress + OffsetINSection;
          return RVA;
        }
      pimage_section_header++;
    }
  return 0;
}
