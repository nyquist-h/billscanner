#include "mainWindow.h"
#include "ui_main.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("GNU-Cache Bill Importer");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
