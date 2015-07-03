#ifndef ERRORHANDLER_H_MP6DJMFS
#define ERRORHANDLER_H_MP6DJMFS

#include "gnucache-bill-importer.h"

#include <exception>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <chrono>

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
    ErrorMessages& operator=(const ErrorMessages&) = delete;

    static ErrorMessages& getInstance();
    std::string getErrorMessage(Error);
};

class ImageLoaderException : public std::exception
{
  private:
    const int m_lineNumber = 0;
    const std::chrono::system_clock::time_point m_timeStamp = std::chrono::system_clock::now();

    const std::string m_functionName;
    const Error m_error;
    const std::string m_message;

  public:
    ImageLoaderException(const std::string&, int, Error);
    ImageLoaderException(const std::string&, int, Error, const std::string&);
    const char* what() const noexcept;
};

class ErrorHistory
{
  private:
    std::vector<std::unique_ptr<std::exception>> m_errorHistory;

    ErrorHistory() = default;

  public:
    ErrorHistory(const ErrorHistory&) = delete;
    ErrorHistory& operator=(const ErrorHistory&) = delete;

    static ErrorHistory& getInstance();

    void addError(const std::exception&);
    const char* lastErrorMessage() const;
    const std::exception& lastError() const;
};

//--------------------------------C API---------------------------------------//
extern "C"
{
  EXPORT short errorHappend(); //020715-TODOnyquistDev return error code
  EXPORT const char* getError(); //020715-TODOnyquistDev return error code
}

#endif /* end of include guard: ERRORHANDLER_H_MP6DJMFS */
