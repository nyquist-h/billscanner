#include "imageLoader.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

using namespace std;
using cv::imread;
using cv::Mat;
using cv::VideoCapture;

std::string to_string(DeviceTyp deviceTyp)
{
  return PRINT(deviceTyp);
}

/**
 * @brief Loads an image from a file
 * @param location The location of the file on the disc
 * @return The loaded image
 */
Mat ImageReader::loadImage(const string& location)
{
  Mat image = imread(location, CV_LOAD_IMAGE_COLOR);
  if(image.data == nullptr) //TODOmmer NULL
    throw ImageLoaderException(__func__, __LINE__, Error::UnableToLoadImageFromFile, location);
  return image;
}

/**
 * @brief Scans an image with an scanner
 * @param
 * @return The scanned Image 
 */
Mat ImageScanner::loadImage(const string& /*device*/)
{
  //TODO error handling
  assert("Not implemented!");
  return Mat();
}

/**
 * @brief Captures an image from a camera
 * @param device The Camera ID
 * @return The captured image
 */
Mat ImageTaker::loadImage(const string& device)
{
  VideoCapture camera(stoi(device)); //stoi TODO?
  if(!camera.isOpened())
    throw ImageLoaderException(__func__, __LINE__, Error::UnableToLoadImageFromWebcam, device);

  Mat image;
  camera >> image;
  return image;
}

/**
 * @brief Creates the right image-loader object
 * @param deviceTyp The type of the input device
 */
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
      throw ImageLoaderException(__FILE__, __LINE__, Error::UnknownDeviceType, to_string(deviceTyp));
  }
}

/**
 * @brief Returns the pointer to the image-loader object
 * @return The image-loader object
 */
shared_ptr<ImageLoader> ImageLoaderFactory::getImageLoader() const
{
  return m_imageLoader;
}

/**
 * @brief Returns the loaded image to the function caller
 * @param deviceTyp The device type from which to load the image
 * @param device The device from which to load the image
 * @return The loaded image
 */
EXPORT CvMat getImage(DeviceTyp deviceTyp, std::string device)
{
  std::shared_ptr<ImageLoader> imageLoader;
  try
  {
    ImageLoaderFactory imageLoaderFactory(deviceTyp);
    imageLoader = imageLoaderFactory.getImageLoader();
  }
  catch(const exception& exception)
  {
    //TODO logging show: exception.what();
    CvMat nullMat;
    return nullMat;
  }

  return imageLoader->loadImage(device);
}

