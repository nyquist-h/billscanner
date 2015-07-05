#include "errorHandler.h"
#include "imageLoader.h"

#include "gtest/gtest.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <memory>
#include <string>

using namespace std;
using cv::Mat;
using cv::imread;


/**
 * @brief Test - Loading an existent Image form disk
 */
TEST(ImageLoader_Test,ImageReaderGetValidImage)
{
  ImageLoaderFactory imageLoaderCreator {DeviceTyp::Disk};
  ImageLoader& m_imageLoader {imageLoaderCreator.getImageLoader()};
  string location {"../../test/data/imageLoaderTestImage.jpg"};
  unique_ptr<Mat> loadedImage = m_imageLoader.loadImage(location);
  Mat originalImage{ imread(location, CV_LOAD_IMAGE_COLOR) };
  Mat result(*loadedImage == originalImage);
  EXPECT_EQ(255, result.at<unsigned char>(0,0));
}

/**
 * @brief Test - Loading an nonexistent image form disk
 */
TEST(ImageLoader_Test,ImageReaderGetNonExistentImage)
{
  ImageLoaderFactory imageLoaderCreator(DeviceTyp::Disk);
  ImageLoader& m_imageLoader {imageLoaderCreator.getImageLoader()};
  string location {"../../test/data/NonExistentTestImage.jpg"};
  Mat loadedImage;
  ASSERT_THROW(m_imageLoader.loadImage(location), ImageLoaderException);
}

