#include "gnucache-bill-importer.h"

#include <iostream>
//#include <fstream>
#include <string>
//#include <functional>
#include <assert.h>

using namespace std;

ErrorMessages::ErrorMessages()
{
  m_errors[Error::UnableToLoadImageFromFile] = "Unable to load image form file!";
  m_errors[Error::UnableToLoadImageFromWebcam] = "Unable to load image form web cam!";
  m_errors[Error::UnableToLoadImageFromsScanner] = "Unable to load image form scanner!";
  m_errors[Error::UnknownDeviceType] = "Unknown device type!";

  assert(m_errors.size() == static_cast<size_t>(Error::Count));
}

ErrorMessages& ErrorMessages::getInstance()
{
  static ErrorMessages instance;
  return instance;
}

string ErrorMessages::getErrorMessage(Error error)
{
  return m_errors[error];
}

ImageLoaderException::ImageLoaderException(const string& functionName, unsigned int lineNumber,
    Error errorCode)
  : m_functionName(functionName), 
    m_lineNumber(lineNumber), 
    m_message(ErrorMessages::getInstance().getErrorMessage(errorCode)) 
{ 
 //TODO logging
}

ImageLoaderException::ImageLoaderException(const string& functionName, unsigned int lineNumber,
    Error errorCode, const std::string& additionalInformations)
  : m_functionName(functionName), 
    m_lineNumber(lineNumber), 
    m_message(ErrorMessages::getInstance().getErrorMessage(errorCode) + 
              " Additional Information: " + additionalInformations) 
{ 
 //TODO logging
}

const char* ImageLoaderException::what() const noexcept
{
 return m_message.c_str(); 
}

int main()
{
  ErrorMessages::getInstance();
  string str;
  cout << __FILE__<< endl;
  return 0;
}

