#include "pedumpmainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "antiDebug.h"
#include "antiDebug2.h"
#include <qinputdialog.h>
int main(int argc, char *argv[])
{


  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
      const QString baseName = "PEDump_" + QLocale(locale).name();
      if (translator.load(":/i18n/" + baseName)) {
          a.installTranslator(&translator);
          break;
        }
    }

  PEDumpMainWindow w;


  w.show();
  return a.exec();
}
