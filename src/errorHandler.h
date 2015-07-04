#ifndef ERRORHANDLER_H_MP6DJMFS
#define ERRORHANDLER_H_MP6DJMFS

#include "gnucache-bill-importer.h"

#include <exception>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <chrono>

#define ERROR_LOCATION __FILE__, __func__, __LINE__

enum class ErrorCode
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
    std::map<ErrorCode, std::string> m_errors;

    ErrorMessages();

  public:
    ErrorMessages(const ErrorMessages&) = delete;
    ErrorMessages& operator=(const ErrorMessages&) = delete;

    static ErrorMessages& getInstance();
    std::string getErrorMessage(ErrorCode);
};

class GnuCacheBillImporterException : public std::exception
{
  public:
    virtual const char* what() const noexcept = 0;
    virtual void print(std::ostream&) const = 0;

    friend std::ostream& operator<<(std::ostream& stream, const GnuCacheBillImporterException& error);
};

//040715-TODOnyquistDev check if needed std::ostream& operator<<(std::ostream& stream, const GnuCacheBillImporterException& error);

class ImageLoaderException : public GnuCacheBillImporterException
{
  private:
    const std::chrono::system_clock::time_point m_timeStamp = std::chrono::system_clock::now();

    const std::string m_fileName;
    const std::string m_functionName;
    const int m_lineNumber = 0;
    const std::string m_message;

  public:
    ImageLoaderException(const std::string&, const std::string&, int, ErrorCode);
    ImageLoaderException(const std::string&, const std::string&, int, ErrorCode, const std::string&);

    const char* what() const noexcept;
    void print(std::ostream&) const;
};

class ErrorHistory
{
  private:
    std::vector<std::unique_ptr<std::exception>> m_errorHistory;
    std::vector<std::exception*> m_unhandledErrors;

    ErrorHistory() = default;

  public:
    ErrorHistory(const ErrorHistory&) = delete;
    ErrorHistory& operator=(const ErrorHistory&) = delete;

    static ErrorHistory& getInstance();

    void addError(const std::exception&);
    const char* lastErrorMessage() const;
    const std::exception& lastError() const;
    bool unhandledErrors();
};

//--------------------------------C API---------------------------------------//
extern "C"
{
  EXPORT short errorHappend(); //020715-TODOnyquistDev return error code
  EXPORT const char* getError(); //020715-TODOnyquistDev return error code
}

#endif /* end of include guard: ERRORHANDLER_H_MP6DJMFS */
