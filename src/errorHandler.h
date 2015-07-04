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
  protected:
    const std::chrono::system_clock::time_point m_timeStamp = std::chrono::system_clock::now();

  public:
    virtual const char* what() const noexcept = 0;
    virtual void print(std::ostream&) const = 0;

    friend std::ostream& operator<<(std::ostream& stream, const GnuCacheBillImporterException& error);
};
//040715-TODOnyquistDev check if needed std::ostream& operator<<(std::ostream& stream, const GnuCacheBillImporterException& error);

class CustomException : public GnuCacheBillImporterException
{
  private:
    const std::string m_errorMessage;

  public:
    CustomException(const std::string&);
    virtual const char* what() const noexcept;
    virtual void print(std::ostream&) const;
};


class ImageLoaderException : public GnuCacheBillImporterException
{
  private:
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
    std::vector<std::unique_ptr<GnuCacheBillImporterException>> m_errorHistory;
    std::vector<GnuCacheBillImporterException*> m_unhandledErrors;

    ErrorHistory() = default;

  public:
    ErrorHistory(const ErrorHistory&) = delete;
    ErrorHistory& operator=(const ErrorHistory&) = delete;

    static ErrorHistory& getInstance();

    //050715-TODOnyquistDev void addError(const GnuCacheBillImporterException&);
    const char* lastErrorMessage() const;
    GnuCacheBillImporterException* handleError();
    int unhandledErrors() const;
};

//--------------------------------C API---------------------------------------//
extern "C"
{
  EXPORT int errorHappend(); //020715-TODOnyquistDev return error code
  EXPORT const char* getError(); //020715-TODOnyquistDev return error code
}

#endif /* end of include guard: ERRORHANDLER_H_MP6DJMFS */
