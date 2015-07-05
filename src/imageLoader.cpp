#include "imageLoader.h"
#include "errorHandler.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <set>
#include <functional>
#include <memory>

using namespace std;
using cv::imread;
using cv::Mat;
using cv::VideoCapture;

//020715-TODOnyquistDev export to loadedimage class and use custom compare function
auto cmp = [](const unique_ptr<Mat>& imageA, const unique_ptr<Mat>& imageB)
{
  //040715-TODOnyquistDev implement the right way
  //Mat output(imageA->size(), imageB->type());
  //cv::compare(*imageA, *imageB, output, cv::CMP_LT);
  return imageA->rows < imageB->rows;
};
set<unique_ptr<Mat>, decltype(cmp)> loadedImages(cmp);

/**
 * @brief Loads an image from a file
 * @param location The location of the file on the disc
 * @return The loaded image
 */
unique_ptr<Mat> ImageReader::loadImage(const string& location)
{
  unique_ptr<Mat> image = make_unique<Mat>(imread(location, CV_LOAD_IMAGE_COLOR));
  if(image->data == nullptr) //020715-TODOnyquistDev NULL
    throw ImageLoaderException(ERROR_LOCATION, ErrorCode::UnableToLoadImageFromFile, location);
  return image;
}

/**
 * @brief Scans an image with an scanner
 * @param device The Scanner ID
 * @return The scanned Image
 */
unique_ptr<Mat> ImageScanner::loadImage(const string& /*device*/)
{
  //TODO error handling
  assert("Not implemented!");
  return nullptr;
}

/**
 * @brief Captures an image from a camera
 * @param device The Camera ID
 * @return The captured image
 */
unique_ptr<Mat> ImageTaker::loadImage(const string& device)
{
  VideoCapture camera(stoi(device));
  if(!camera.isOpened())
    throw ImageLoaderException(ERROR_LOCATION, ErrorCode::UnableToLoadImageFromWebcam, device);

  unique_ptr<Mat> image = make_unique<Mat>();
  camera >> *image;
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
      m_imageLoader = make_unique<ImageReader>(ImageReader());
      break;
    case DeviceTyp::Scanner:
      m_imageLoader = make_unique<ImageScanner>(ImageScanner());
      break;
    case DeviceTyp::Webcam:
      m_imageLoader = make_unique<ImageTaker>(ImageTaker());
      break;
    default:
      throw ImageLoaderException(ERROR_LOCATION, ErrorCode::UnknownDeviceType, PRINT(deviceTyp));
  }
}

/**
 * @brief Returns the pointer to the image-loader object
 * @return The image-loader object
 */
ImageLoader& ImageLoaderFactory::getImageLoader() const
{
  return *m_imageLoader;
}

//--------------------------------C API---------------------------------------//
/**
 * @brief Returns the loaded image to the function caller
 * @param deviceTyp The device type from which to load the image
 * @param device The device from which to load the image
 * @return A pointer to the loaded image or to an empty image if an error occurred
 */
EXPORT CvMat getImage(DeviceTyp deviceTyp, const char* device)
{
  try
  {
    ImageLoaderFactory imageLoaderFactory {deviceTyp};
    ImageLoader& imageLoader {imageLoaderFactory.getImageLoader()};

    auto picture = loadedImages.begin();
    bool success {false};
    tie(picture, success) = loadedImages.insert(imageLoader.loadImage(device));
    if(!success)
      throw ImageLoaderException(ERROR_LOCATION, ErrorCode::ImageAlreadyLoaded, "Location: "s + device);

    return *picture->get();
  }
  catch(const GnuCacheBillImporterException& except)
  {
    //020715-TODOnyquistDev logging show: exception.what();
    ErrorHistory::getInstance().addError(except);
    return CvMat();
  }
  catch(exception& except)
  {
    //040715-TODOnyquistDev
    ErrorHistory::getInstance().addError(CustomException(except.what()));
    return CvMat();
  }
}

