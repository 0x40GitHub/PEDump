#include "formeditpefile.h"
#include "qdebug.h"
#include "ui_formeditpefile.h"
#include "peutils.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
FormEditPEFile::FormEditPEFile(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FormEditPEFile)
{
  ui->setupUi(this);
}

FormEditPEFile::~FormEditPEFile()
{
  delete ui;
}

void FormEditPEFile::ReceiveImageBase(LPVOID ImageBase)
{
  this->ImageBase = ImageBase;
}

void FormEditPEFile::on_pushButtonInsertSection_clicked()
{
  this->ImageBase = AddSection(this->ImageBase, 0x1000);
}


void FormEditPEFile::on_pushButtonSave_clicked()
{
    LPVOID FileBuffer = nullptr;
    DWORD SizeOfFileBuffer = 0;
    SizeOfFileBuffer=ImageBufferToFileBuffer(this->ImageBase, FileBuffer);

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
    aFile.write((const char*)FileBuffer, SizeOfFileBuffer);
}


void FormEditPEFile::on_pushButtonExpandSection_clicked()
{   DWORD Increment = ui->lineEdit->text().toInt();
    this->ImageBase = ExpandSection(this->ImageBase, Increment);
}


void FormEditPEFile::on_pushButtonSaveExpandSection_clicked()
{
  LPVOID FileBuffer = nullptr;
  DWORD SizeOfFileBuffer = 0;
  SizeOfFileBuffer=ImageBufferToFileBuffer(this->ImageBase, FileBuffer);

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
  aFile.write((const char*)FileBuffer, SizeOfFileBuffer);
}


void FormEditPEFile::on_pushButtonMerge_clicked()
{
  this->ImageBase = MergeSection(this->ImageBase);
}



void FormEditPEFile::on_pushButtonSaveMerge_clicked()
{
  LPVOID FileBuffer = nullptr;
  DWORD SizeOfFileBuffer = 0;
  SizeOfFileBuffer=ImageBufferToFileBuffer(this->ImageBase, FileBuffer);

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
  aFile.write((const char*)FileBuffer, SizeOfFileBuffer);
}



