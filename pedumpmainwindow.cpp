#include "pedumpmainwindow.h"
#include "ui_pedumpmainwindow.h"
#include "qhexview.h"
#include <QDir>
#include <QFileDialog>
#include <QMdiSubWindow>
#include "document/qhexdocument.h"
#include "document/buffer/qmemorybuffer.h"
#include "formmsdosheader.h"
#include "peutils.h"
#include "formntheaders.h"
#include "formfileheader.h"
#include "formoptionalheader.h"
#include "formsections.h"
#include "formdatadirectory.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include "formeditpefile.h"
#include "formrvatofoa.h"
#include <QSplitter>
PEDumpMainWindow::PEDumpMainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::PEDumpMainWindow)
{
  ui->setupUi(this);
  this->setCentralWidget(ui->mdiArea);
  this->setAcceptDrops(true); //必须设置，不然无法接收拖放事件
  //this->setWindowState(Qt::WindowMaximized);
  // 子窗口显示模式
  ui->mdiArea->setViewMode(QMdiArea::TabbedView);
  ui->mdiArea->setTabsClosable(true);


}

PEDumpMainWindow::~PEDumpMainWindow()
{
  delete ui;
}

void PEDumpMainWindow::dragEnterEvent(QDragEnterEvent *event)
{
  if(event->mimeData()->hasUrls())
    {
      event->acceptProposedAction(); //事件数据中存在路径，方向事件
    }
  else
    {
      event->ignore();
    }
}

void PEDumpMainWindow::dropEvent(QDropEvent *event)
{
  const QMimeData *mimeData = event->mimeData();
  if(mimeData->hasUrls() )
    {
      QList<QUrl> urls = mimeData->urls();
      QString aFileName = urls.at(0).toLocalFile();
      bool needNew = false;
      QHexView* phex_view = nullptr;
      QHexView* phex_view1 = nullptr;


      if (ui->mdiArea->subWindowList().count() > 0) {
          phex_view = (QHexView*)ui->mdiArea->activeSubWindow();
          phex_view1 = (QHexView*)ui->mdiArea->activeSubWindow();
          needNew = phex_view->isFileOpened();
        } else {
          needNew = true;
        }
      if (needNew) {
          phex_view = new QHexView;
          phex_view1 = new QHexView;
          ui->mdiArea->addSubWindow(phex_view);
          ui->mdiArea->addSubWindow(phex_view1);
        }

      // 打开文件
      phex_view->loadFromFile(aFileName.toStdWString().c_str());
      if (phex_view->isFileOpened()) {
          phex_view->setWindowTitle(aFileName);
          phex_view1->setWindowTitle(aFileName + " In Memory");
        }

      QHexDocument* document = QHexDocument::fromFile<QMemoryBuffer>(aFileName); // raw dat
      QHexDocument* document1 = QHexDocument::fromMemory<QMemoryBuffer>(GetImage(phex_view->mMapFileStruct.ImageBase), GetOptionalHeader(phex_view->mMapFileStruct.ImageBase)->SizeOfImage);

      phex_view->setDocument(document);
      phex_view1->setDocument(document1);


      phex_view->show();
      phex_view1->show();


    }
}

// 菜单项：打开的事件响应
void PEDumpMainWindow::on_actionOpen_triggered()
{
  bool needNew = false;
  QHexView* phex_view = nullptr;
  QHexView* phex_view1 = nullptr;

  if (ui->mdiArea->subWindowList().count() > 0) {
      phex_view = (QHexView*)ui->mdiArea->activeSubWindow();
      phex_view1 = (QHexView*)ui->mdiArea->activeSubWindow();
      needNew = phex_view->isFileOpened();
    } else {
      needNew = true;
    }

  QString currPath = QDir::currentPath();
  QString aFileName = QFileDialog::getOpenFileName(this, "Open a file", currPath, "pe file(*.exe *.dll)");
  if (needNew) {
      phex_view = new QHexView;
      phex_view1 = new QHexView;
      ui->mdiArea->addSubWindow(phex_view);
      ui->mdiArea->addSubWindow(phex_view1);
    }

  // 打开文件
  phex_view->loadFromFile(aFileName.toStdWString().c_str());
  if (phex_view->isFileOpened()) {
      phex_view->setWindowTitle(aFileName);
      phex_view1->setWindowTitle(aFileName + " In Memory");
    }

  QHexDocument* document1 = QHexDocument::fromMemory<QMemoryBuffer>(GetImage(phex_view->mMapFileStruct.ImageBase), GetOptionalHeader(phex_view->mMapFileStruct.ImageBase)->SizeOfImage);
  QHexDocument* document = QHexDocument::fromFile<QMemoryBuffer>(aFileName); // raw data
  phex_view1->setDocument(document1);
  phex_view->setDocument(document);


  phex_view1->show();
  phex_view->show();

}

// MS-DOS Header 工具响应
void PEDumpMainWindow::on_actionMS_DOS_Header_triggered()
{
  if (ui->mdiArea->subWindowList().count() == 0) {
      return;
    }
  // get active widget
  QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());

  PIMAGE_DOS_HEADER pimage_dos_header = GetMSDOSHeader(phex_view->mMapFileStruct.ImageBase);

  // show ms-dos header
  FormMSDOSHeader* pform_msdos_header = new FormMSDOSHeader;

  pform_msdos_header->ShowInfo(pimage_dos_header);
  pform_msdos_header->show();


}

// NT Headers 工具响应
void PEDumpMainWindow::on_actionNT_Headers_triggered()
{
  if (ui->mdiArea->subWindowList().count() == 0) {
      return;
    }
  // get active widget
  QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());

  PIMAGE_NT_HEADERS  pimage_nt_headers = GetNTHeaders(phex_view->mMapFileStruct.ImageBase);

  // show nt headers
  FormNTHeaders* pform_nt_headers = new FormNTHeaders;

  pform_nt_headers->ShowInfo(pimage_nt_headers, phex_view->mMapFileStruct.ImageBase);
  pform_nt_headers->show();
}

// File Header 工具响应
void PEDumpMainWindow::on_actionFile_Header_triggered()
{
  if (ui->mdiArea->subWindowList().count() == 0) {
      return;
    }
  // get active widget
  QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());
  PIMAGE_FILE_HEADER pimage_file_header = GetFileHeader(phex_view->mMapFileStruct.ImageBase);

  // show file header
  FormFileHeader* pform_file_header = new FormFileHeader;
  pform_file_header->ImageBase = phex_view->mMapFileStruct.ImageBase;
  pform_file_header->ShowInfo(pimage_file_header, phex_view->mMapFileStruct.ImageBase);
  pform_file_header->show();
}

// Optional Header 工具响应
void PEDumpMainWindow::on_actionOptionalHeader_triggered()
{
  if (ui->mdiArea->subWindowList().count() == 0) {
      return;
    }
  // get active widget
  QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());
  PIMAGE_OPTIONAL_HEADER pimage_optional_header = GetOptionalHeader(phex_view->mMapFileStruct.ImageBase);

  // show optional header
  FormOptionalHeader* pform_optional_header = new FormOptionalHeader;
  pform_optional_header->ShowInfo(pimage_optional_header, phex_view->mMapFileStruct.ImageBase);
  pform_optional_header->show();
}

// Sections 工具响应
void PEDumpMainWindow::on_actionSections_triggered()
{
  if (ui->mdiArea->subWindowList().count() == 0) {
      return;
    }
  // get active widget
  QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());
  FormSections* pform_sections = new FormSections;
  pform_sections->ShowInfo(phex_view->mMapFileStruct.ImageBase);
  pform_sections->show();


}
// DataDirectory 工具响应

void PEDumpMainWindow::on_actionDataDirectory_triggered()
{
  if (ui->mdiArea->subWindowList().count() == 0) {
      return;
    }
  // get active widget
  QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());
  FormDataDirectory* pform_data_directory = new FormDataDirectory;
  pform_data_directory->ShowInfo(phex_view->mMapFileStruct.ImageBase);
  pform_data_directory->show();
  connect(this, SIGNAL(SendImageBase(LPVOID)), pform_data_directory, SLOT(ReceiveImageBase(LPVOID)));
  if (pform_data_directory) {
      emit this->SendImageBase(phex_view->mMapFileStruct.ImageBase);
    }
}

// 保存文件
void PEDumpMainWindow::on_actionSavePEFile_triggered()
{
  if (ui->mdiArea->subWindowList().count() == 0) {
      return;
    }
  // get active widget
  QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());
  QHexDocument* document = phex_view->getDocument();

  QString curPath = QDir::currentPath();
  QString dlgTitle = "Save PE file!";
  QString filter = "pe file(*.exe *.dll)";
  QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
  if (aFileName.isEmpty()) {
      return;
    }
  QFile aFile(aFileName);
  if (!aFile.open(QIODevice::WriteOnly)) {
      return;
    }

  document->saveTo(dynamic_cast<QIODevice*>(&aFile));
}


void PEDumpMainWindow::on_actionEditPE_triggered()
{
    FormEditPEFile* pform_edit_pe_file = new FormEditPEFile;
    if (ui->mdiArea->subWindowList().count() == 0) {
        return;
      }
    // get active widget
    QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());
    pform_edit_pe_file->show();

    connect(this, SIGNAL(SendImageBase(LPVOID)), pform_edit_pe_file, SLOT(ReceiveImageBase(LPVOID)));
    if (pform_edit_pe_file) {
        emit this->SendImageBase(phex_view->mMapFileStruct.ImageBase);
      }
}


void PEDumpMainWindow::on_actionRVAToFOA_triggered()
{
    if (ui->mdiArea->subWindowList().count() == 0) {
        return;
      }
    // get active widget
    QHexView* phex_view = static_cast<QHexView*>(ui->mdiArea->activeSubWindow()->widget());
    FormRVAToFOA* pform_rva_to_foa = new FormRVAToFOA;
    pform_rva_to_foa->ShowInfo(phex_view->mMapFileStruct.ImageBase);
    pform_rva_to_foa->show();
}

