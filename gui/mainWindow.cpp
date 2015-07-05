#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QWidget>
#include <QImage>
#include <QPainter>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "../src/imageLoader.h" //TODO change include path
#include "../src/errorHandler.h" //TODO change include path

#include <opencv2/highgui/highgui.hpp>

using namespace std;
using cv::Mat;

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
  //020715-TODOnyquistDev just a demo
  CvMat cvLoadedImage {getImage(DeviceTyp::Disk, "/home/nyquist/projects/gnucash-bill-importer/test/data/imageLoaderTestImage.jpg")};
  Mat loadedImage(&cvLoadedImage);
  Mat image(loadedImage.size(), CV_8UC3);

  switch (loadedImage.type())
  {
    case CV_8UC1:
      cvtColor(loadedImage, image, CV_GRAY2RGB);
      break;
    case CV_8UC3:
      cvtColor(loadedImage, image, CV_BGR2RGB);
      break;
  }

  //QImage needs the data to be stored continuously in memory
  assert(image.isContinuous());
  m_displayedImage = QImage(image.data, image.cols, image.rows, image.cols*3, QImage::Format_RGB888);

  this->ui->pictureLabel->setPixmap(QPixmap::fromImage(m_displayedImage));
  this->ui->pictureLabel->show();
}
