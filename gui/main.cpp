#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPainter>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("GNU-Cache Bill Importer");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
