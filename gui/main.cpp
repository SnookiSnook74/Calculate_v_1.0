#include <QApplication>
#include <QLocale>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QLocale::setDefault(QLocale::c());
  MainWindow w;
  w.show();
  return a.exec();
}
