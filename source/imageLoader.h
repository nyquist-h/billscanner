#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "gnucache-bill-importer.h"

#include <opencv2/core/core.hpp>

#include <string>
#include <memory>

//TODO install doxygentoolkit plugin
class ImageLoader
{
  public:
    ImageLoader();
    virtual cv::Mat loadImage(std::string) = 0;
    virtual ~ImageLoader();
};

class ImageReader : public ImageLoader
{
  public:
    ImageReader();
    cv::Mat loadImage(std::string);
    virtual ~ImageReader();
};

class ImageScanner : public ImageLoader
{
  public:
    ImageScanner();
    cv::Mat loadImage(std::string);
    virtual ~ImageScanner();
};

class ImageTaker : public ImageLoader
{
  public:
    ImageTaker();
    cv::Mat loadImage(std::string);
    virtual ~ImageTaker();
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
    std::shared_ptr<ImageLoader> m_imageLoader;

  public:
    ImageLoaderFactory(DeviceTyp);
    std::shared_ptr<ImageLoader> getImageLoader() const;
    virtual ~ImageLoaderFactory();
};


extern "C" {

EXPORT CvMat getImage(DeviceTyp, std::string);

}// extern "C"

#endif /* end of include guard: IMAGELOADER_H */

