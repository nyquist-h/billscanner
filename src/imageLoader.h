#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "gnucache-bill-importer.h"

#include <opencv2/core/core.hpp>
#include <string>
#include <memory>

class ImageLoader
{
  public:
    virtual std::unique_ptr<cv::Mat> loadImage(const std::string&) = 0;
    virtual ~ImageLoader(){}
};

class ImageReader : public ImageLoader
{
  public:
    std::unique_ptr<cv::Mat> loadImage(const std::string&);
};

class ImageScanner : public ImageLoader
{
  public:
    std::unique_ptr<cv::Mat> loadImage(const std::string&);
};

class ImageTaker : public ImageLoader
{
  public:
    std::unique_ptr<cv::Mat> loadImage(const std::string&);
};

enum class DeviceTyp
{
  Disk,
  Scanner,
  Webcam
};

class ImageLoaderFactory
{
  private:
    std::unique_ptr<ImageLoader> m_imageLoader;

  public:
    ImageLoaderFactory(DeviceTyp);
    ImageLoader& getImageLoader() const;
    virtual ~ImageLoaderFactory(){}
};

//--------------------------------C API---------------------------------------//
extern "C" 
{
  EXPORT CvMat getImage(DeviceTyp, const char*);
  EXPORT void deleteImage(CvMat);
}

#endif /* end of include guard: IMAGELOADER_H */

