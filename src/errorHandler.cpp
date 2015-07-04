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
std::ostream& operator<<(std::ostream& stream, const GnuCacheBillImporterException& error)
{
  error.print(stream);
  return stream;
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
  auto now = chrono::system_clock::to_time_t(m_timeStamp);
  stream <<  put_time(localtime(&now), "%c") << " ";
  stream << "Line: " << m_lineNumber << " ";
  stream << "Function: " << m_lineNumber << " ";
  stream << "Error: " << m_lineNumber << " ";
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

/**
 * @brief Adds an error to the history
 * @param sError The error which happened
 */
void ErrorHistory::addError(const std::exception& sError)
{
  m_errorHistory.emplace_back(make_unique<std::exception>(sError)); //040715-TODOnyquistDev throws
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
const std::exception& ErrorHistory::lastError() const
{
  return *(m_errorHistory.back());
}

bool ErrorHistory::unhandledErrors()
{
//040715-TODOnyquistDev continue

}

//--------------------------------C API---------------------------------------//
EXPORT short errorHappend()
{
  //return
}
