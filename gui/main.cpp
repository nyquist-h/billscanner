#include "main.h"
#include "ui_main.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Main)
{
    ui->setupUi(this);
    this->setWindowTitle("GNU-Cache Bill Importer");
}

MainWindow::~MainWindow()
{
    delete ui;
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setApplicationName("GNU-Cache Bill Importer");
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
