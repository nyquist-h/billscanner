#include "mainWindow.h"
#include "ui_main.h"
#include <QMessageBox>

#include <opencv2/core/core.hpp>
#include "../../src/imageLoader.h" //TODO change include path

using namespace std;

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

void MainWindow::on_load_btn_clicked()
{
    QMessageBox msgBox;
    CvMat image = getImage(DeviceTyp::Disk, "/home/nyquist/projects/gnucash-bill-importer/test/data/imageLoaderTestImage.jpg");
    msgBox.setText("The document has been modified."); //TODO change
    msgBox.exec();
}
