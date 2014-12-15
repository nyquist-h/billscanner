#include "imageLoader.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace std;
using cv::imread;
using cv::Mat;
using cv::VideoCapture;

Mat ImageReader::loadImage(string location) 
{
  Mat image = imread(location, CV_LOAD_IMAGE_COLOR);
  return image;
}

Mat ImageScanner::loadImage(string device) 
{
  //TODO
  Mat image;
  return image;
}

Mat ImageTaker::loadImage(string device) 
{
  VideoCapture camera(stoi(device));
  //if(!cameta.isOpened()) 
    //TODO throw exception

  Mat image;
  camera >> image;
  return image;
}

ImageLoaderFactory::ImageLoaderFactory(DeviceTyp deviceTyp) 
{
  switch(deviceTyp)
  {
    case DeviceTyp::Disk:
      m_imageLoader = make_shared<ImageReader>(new ImageReader());
      break;
    case DeviceTyp::Scanner:
      m_imageLoader = make_shared<ImageScanner>(new ImageScanner());
      break;
    case DeviceTyp::Webcam:
      m_imageLoader = make_shared<ImageTaker>(new ImageTaker());
      break;
    default:
      break;
      //TODO throw exception
  }
}

shared_ptr<ImageLoader> ImageLoaderFactory::getImageLoader() const
{
  return m_imageLoader;
}

EXPORT CvMat getImage(DeviceTyp deviceTyp, std::string device)
{
  ImageLoaderFactory imageLoaderFactory(deviceTyp);
  std::shared_ptr<ImageLoader> imageLoader = imageLoaderFactory.getImageLoader();

  return imageLoader->loadImage(device);
}
