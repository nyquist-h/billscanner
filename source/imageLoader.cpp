#include "imageLoader.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace std;
using cv::imread;
using cv::Mat;
using cv::VideoCapture;

//TODO install doxygentoolkit plugin, comment
ImageLoader::ImageLoader(){};
ImageLoader::~ImageLoader(){};

ImageReader::ImageReader(){};
ImageReader::~ImageReader(){};
Mat ImageReader::loadImage(const string& location) 
{
  Mat image = imread(location, CV_LOAD_IMAGE_COLOR);
  return image;
}

ImageScanner::ImageScanner(){};
ImageScanner::~ImageScanner(){};
Mat ImageScanner::loadImage(const string& /*device*/) 
{
  //TODO
  Mat image;
  return image;
}

ImageTaker::ImageTaker(){};
ImageTaker::~ImageTaker(){};
Mat ImageTaker::loadImage(const string& device) 
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
      m_imageLoader = shared_ptr<ImageReader>(new ImageReader());
      break;
    case DeviceTyp::Scanner:
      m_imageLoader = shared_ptr<ImageScanner>(new ImageScanner());
      break;
    case DeviceTyp::Webcam:
      m_imageLoader = shared_ptr<ImageTaker>(new ImageTaker());
      break;
    default:
      throw ImageLoaderException(__FILE__, __LINE__, "Unknown device!");
  }
}

shared_ptr<ImageLoader> ImageLoaderFactory::getImageLoader() const
{
  return m_imageLoader;
}

EXPORT CvMat getImage(DeviceTyp deviceTyp, std::string device)
{
  std::shared_ptr<ImageLoader> imageLoader;
  try 
  {
    ImageLoaderFactory imageLoaderFactory(deviceTyp);
    imageLoader = imageLoaderFactory.getImageLoader();
  }catch(std::exception& exception)
  {
    //TODO logging show: exception.what();
    CvMat nullMat;
    return nullMat;
  }

  return imageLoader->loadImage(device);
}
