#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QMessageBox>
#include <QWidget>
#include <QImage>
#include <QPainter>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "../src/imageLoader.h" //TODO change include path

#include <opencv2/highgui/highgui.hpp>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
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
    //CvMat cvimage = getImage(DeviceTyp::Disk, "/home/nyquist/projects/gnucash-bill-importer/test/data/imageLoaderTestImage.jpg");
    CvMat cvimage = loadImage("/home/nyquist/projects/gnucash-bill-importer/test/data/imageLoaderTestImage.jpg");

    msgBox.setText("The document has been modified."); //TODO change
    msgBox.exec();

    cv::Mat tmp(&cvimage);
    cv::Mat image(tmp.size(), CV_8UC3);
    //tmp.copyTo(image);

    switch (tmp.type())
    {
      case CV_8UC1:
        cvtColor(tmp, image, CV_GRAY2RGB);
        break;
      case CV_8UC3:
        cvtColor(tmp, image, CV_BGR2RGB);
        break;
    }

     //QImage needs the data to be stored continuously in memory
     assert(image.isContinuous());
    _qimage = QImage(image.data, image.cols, image.rows, image.cols*3, QImage::Format_RGB888);

    this->ui->pictureLabel->setPixmap(QPixmap::fromImage(_qimage));

    this->ui->pictureLabel->show();
}
