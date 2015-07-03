#ifndef ERRORHANDLER_H_MP6DJMFS
#define ERRORHANDLER_H_MP6DJMFS

#include "gnucache-bill-importer.h"

#include <exception>
#include <string>
#include <map>

enum class Error
{
  UnableToLoadImageFromFile = 0,
  UnableToLoadImageFromWebcam,
  UnableToLoadImageFromsScanner,
  UnknownDeviceType,
  ImageAlreadyLoaded,

  Count
};

class ErrorMessages
{
  private:
    std::map<Error, std::string> m_errors;

    ErrorMessages();

  public:
    ErrorMessages(const ErrorMessages&) = delete;
    ErrorMessages& operator=(ErrorMessages const&) = delete;

    static ErrorMessages& getInstance();
    std::string getErrorMessage(Error);
};

class ImageLoaderException : public std::exception
{
  private:
    std::string m_functionName;
    int m_lineNumber = 0;
    std::string m_message;

  public:
    ImageLoaderException(const std::string&, int, Error);
    ImageLoaderException(const std::string&, int, Error, const std::string&);
    const char* what() const noexcept;
};

//--------------------------------C API---------------------------------------//
extern "C" 
{
  EXPORT short errorHappend(); //020715-TODOnyquistDev return error code
  EXPORT const char* getError(); //020715-TODOnyquistDev return error code
}

#endif /* end of include guard: ERRORHANDLER_H_MP6DJMFS */
