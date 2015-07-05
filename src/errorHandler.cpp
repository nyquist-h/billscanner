#include "errorHandler.h"

#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <assert.h>
using namespace std;

/**
 * @brief Assigns error messages to the error code
 */
ErrorMessages::ErrorMessages()
{
  m_errors[ErrorCode::UnableToLoadImageFromFile] = "Unable to load image form file!";
  m_errors[ErrorCode::UnableToLoadImageFromWebcam] = "Unable to load image form web cam!";
  m_errors[ErrorCode::UnableToLoadImageFromsScanner] = "Unable to load image form scanner!";
  m_errors[ErrorCode::UnknownDeviceType] = "Unknown device type!";
  m_errors[ErrorCode::ImageAlreadyLoaded] = "Image already loaded";

  assert(m_errors.size() == static_cast<size_t>(ErrorCode::Count));
}

/**
 * @brief Returns the instance of the ErrorMessages Singleton object
 * @return Object which holds all error messages
 */
ErrorMessages& ErrorMessages::getInstance()
{
  static ErrorMessages instance;
  return instance;
}

/**
 * @brief Returns the error message which belongs to the error code
 * @param errorCode The error code
 * @return Error message
 */
string ErrorMessages::getErrorMessage(ErrorCode errorCode)
{
  return m_errors[errorCode];
}

/**
 * @brief Prints all information contained in the exception object
 * @param stream Output stream
 * @param error Exception object
 * @return Output stream
 */
void GnuCacheBillImporterException::print(ostream& stream) const
{
  auto now = chrono::system_clock::to_time_t(m_timeStamp);
  stream <<  put_time(localtime(&now), "%c") << " ";
}

/**
 * @brief Prints all information contained in the exception object
 * @param stream Output stream
 * @param error Exception object
 * @return Output stream
 */
std::ostream& operator<<(std::ostream& stream, const GnuCacheBillImporterException& error)
{
  error.print(stream);
  return stream;
}


/**
 * @brief Constructor of an custom exception
 * @param errorMessage Error message
 */
CustomException::CustomException(const string& errorMessage)
 : m_errorMessage(errorMessage)
{ }

/**
 * @brief Returns the error message of the exception
 * @return Error message
 */
const char* CustomException::what() const noexcept
{
  return m_errorMessage.c_str();
}

/**
 * @brief Prints all information contained in the exception object
 * @param stream Output stream
 * @param error Exception object
 * @return Output stream
 */
void CustomException::print(ostream& stream) const
{
  GnuCacheBillImporterException::print(stream);
  stream << m_errorMessage;
}

/**
 * @brief Creates an copy of the exception and returns an unique_ptr to it
 * @return Unique pointer to the new created exception
 */
std::unique_ptr<GnuCacheBillImporterException> CustomException::copy() const
{
  return std::make_unique<CustomException> (CustomException(*this));
}

/**
 * @brief Exception which is thrown if an image can't be loaded
 * @param functionName The name of the function where the error happened
 * @param lineNumber The line of code where the exception is thrown
 */
ImageLoaderException::ImageLoaderException(const string& fileName, const string& functionName,
    int lineNumber, ErrorCode errorCode)
  : m_fileName(fileName),
    m_functionName(functionName),
    m_lineNumber(lineNumber),
    m_message(ErrorMessages::getInstance().getErrorMessage(errorCode))
{
 //TODO logging
}

/**
 * @brief Exception which is thrown if an image can't be loaded
 * @param functionName The name of the function where the error happened
 * @param lineNumber The line of code where the exception is thrown
 * @param additionalInformations Additional information about the error
 */
ImageLoaderException::ImageLoaderException(const string& fileName, const string& functionName,
    int lineNumber, ErrorCode errorCode, const std::string& additionalInformations)
  : m_fileName(fileName),
    m_functionName(functionName),
    m_lineNumber(lineNumber),
    m_message(ErrorMessages::getInstance().getErrorMessage(errorCode) +
              " Additional Information: " + additionalInformations)
{
 //TODO logging
}

/**
 * @brief Returns the message saved in the exception
 * @return Error message + additional information
 */
const char* ImageLoaderException::what() const noexcept
{
  return m_message.c_str();
}

void ImageLoaderException::print(ostream& stream) const
{
  GnuCacheBillImporterException::print(stream);
  stream << "Line: " << m_lineNumber << " ";
  stream << "Function: " << m_lineNumber << " ";
  stream << "Error: " << m_lineNumber << " ";
}

/**
 * @brief Creates an copy of the exception and returns an unique_ptr to it
 * @return Unique pointer to the new created exception
 */
std::unique_ptr<GnuCacheBillImporterException> ImageLoaderException::copy() const
{
  return std::make_unique<ImageLoaderException> (ImageLoaderException(*this));
}

/**
 * @brief Returns the instance of the ErrorHistory Singleton object
 * @return The error history
 */
ErrorHistory& ErrorHistory::getInstance()
{
  static ErrorHistory instance;
  return instance;
}

//050715-TODOnyquistDev
/**
 * @brief Adds an error to the history
 * @param sError The error which happened
 */
void ErrorHistory::addError(const GnuCacheBillImporterException& sError)
{
  //050715-TODOnyquistDev errorLoger log error sError
  m_errorHistory.emplace_back(sError.copy());
  m_unhandledErrors.push_back(m_errorHistory.back().get());
}

/**
 * @brief Gets the error message from the last error
 * @return Error message from last error
 */
const char* ErrorHistory::lastErrorMessage() const
{
  return m_errorHistory.back()->what();
}

/**
 * @brief Gets the last error
 * @return Last error
 */
GnuCacheBillImporterException* ErrorHistory::handleError()
{
  if(m_unhandledErrors.empty())
    return nullptr;

  GnuCacheBillImporterException* lastError {m_unhandledErrors.back()};
  m_unhandledErrors.pop_back();
  return lastError;
}

/**
 * @brief Return the number of unhandled errors
 * @return Number of unhandled errors
 */
int ErrorHistory::unhandledErrors() const
{
  return m_unhandledErrors.size();
}

//--------------------------------C API---------------------------------------//
EXPORT int errorHappend()
{
  return ErrorHistory::getInstance().unhandledErrors();
}

EXPORT const char* getError()
{
  GnuCacheBillImporterException* error {ErrorHistory::getInstance().handleError()};
  if (error)
    return error->what();
  else
  {
    static std::string noError {"No error happened!"};
    return noError.c_str();
  }
}
