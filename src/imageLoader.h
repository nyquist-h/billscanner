#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "gnucache-bill-importer.h"

#include <opencv2/core/core.hpp>

#include <string>
#include <memory>

class ImageLoader
{
  public:
    ImageLoader();
    virtual cv::Mat loadImage(const std::string&) = 0;
    virtual ~ImageLoader();
};

class ImageReader : public ImageLoader
{
  public:
    cv::Mat loadImage(const std::string&);
};

class ImageScanner : public ImageLoader
{
  public:
    cv::Mat loadImage(const std::string&);
};

class ImageTaker : public ImageLoader
{
  public:
    cv::Mat loadImage(const std::string&);
};

enum class DeviceTyp
{
  Disk,
  Scanner,
  Webcam
};

std::string to_string(DeviceTyp deviceTyp);

class ImageLoaderFactory
{
  private:
    std::shared_ptr<ImageLoader> m_imageLoader;

  public:
    ImageLoaderFactory(DeviceTyp);
    std::shared_ptr<ImageLoader> getImageLoader() const;
    virtual ~ImageLoaderFactory(){}
};


extern "C" {

EXPORT CvMat getImage(DeviceTyp, std::string);

}// extern "C"

#endif /* end of include guard: IMAGELOADER_H */
