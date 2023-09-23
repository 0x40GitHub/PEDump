 #include "formsections.h"
#include "peutils.h"
#include "ui_formsections.h"
#include "formsectionheader.h"

FormSections::FormSections(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormSections)
{
  ui->setupUi(this);
  ui->tabWidget->setVisible(true);
  ui->tabWidget->clear();
  ui->tabWidget->setTabsClosable(true);
}

FormSections::~FormSections()
{
  delete ui;
}

void FormSections::ShowInfo(LPVOID ImageBase)
{
  PIMAGE_SECTION_HEADER pimage_section_header = GetFirstSectionHeader(ImageBase);
  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(ImageBase);
  DWORD NumberOfSections = pimage_file_header->NumberOfSections;

  std::string SectionName;
  for (int i = 0; i < NumberOfSections; i++) {
      FormSectionHeader* pform_section_header = new FormSectionHeader;
      SectionName = (char*)pimage_section_header->Name;
      pform_section_header->ShowInfo(pimage_section_header, ImageBase);
      int cur = ui->tabWidget->addTab(pform_section_header, QString::fromStdString(SectionName));
      ui->tabWidget->setCurrentIndex(cur);
      ui->tabWidget->setVisible(true);
      pimage_section_header++;
    }


}
