#include "errorHandler.h"

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

/**
 * @brief Assigns error messages to error enums
 */
ErrorMessages::ErrorMessages()
{
  m_errors[Error::UnableToLoadImageFromFile] = "Unable to load image form file!";
  m_errors[Error::UnableToLoadImageFromWebcam] = "Unable to load image form web cam!";
  m_errors[Error::UnableToLoadImageFromsScanner] = "Unable to load image form scanner!";
  m_errors[Error::UnknownDeviceType] = "Unknown device type!";
  m_errors[Error::ImageAlreadyLoaded] = "Image already loaded";

  assert(m_errors.size() == static_cast<size_t>(Error::Count));
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
 * @brief Returns the error message which belongs to the Error enum
 * @param error The Error enum
 * @return Error m_message
 */
string ErrorMessages::getErrorMessage(Error error)
{
  return m_errors[error];
}

/**
 * @brief Exception which is thrown if an image can't be loaded
 * @param functionName The name of the function where the error happened
 * @param lineNumber The line of code where the exception is thrown
 * @param errorCode The Error which happened
 */
ImageLoaderException::ImageLoaderException(const string& functionName, int lineNumber,
    Error errorCode)
  : m_lineNumber(lineNumber),
    m_functionName(functionName),
    m_error(errorCode),
    m_message(ErrorMessages::getInstance().getErrorMessage(errorCode))
{
 //TODO logging
}

/**
 * @brief Exception which is thrown if an image can't be loaded
 * @param functionName The name of the function where the error happened
 * @param lineNumber The line of code where the exception is thrown
 * @param errorCode The Error which happened
 * @param additionalInformations Additional information about the error
 */
ImageLoaderException::ImageLoaderException(const string& functionName, int lineNumber,
    Error errorCode, const std::string& additionalInformations)
  : m_lineNumber(lineNumber),
    m_functionName(functionName),
    m_error(errorCode),
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

//--------------------------------C API---------------------------------------//
