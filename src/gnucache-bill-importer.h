#ifndef GNUCACHE_BILL_IMPORTER_H_EUZYAZPN
#define GNUCACHE_BILL_IMPORTER_H_EUZYAZPN

#if defined(_MSC_VER)
  #define EXPORT __declspec(dllexport)
  #define IMPORT __declspec(dllimport)
#elif defined(__GNUG__)
  #define EXPORT __attribute__((visibility("default")))
  #define IMPORT
#elif defined(__llvm__)
  #define EXPORT __attribute__((visibility("default")))
  #define IMPORT
#else
  #error Unknown dynamic link import/export semantics.
#endif

#include <exception>
#include <string>
#include <map>

#define PRINT(variable) #variable

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
    ErrorMessages(const ErrorMessages&); //TODO check if needed in c++ 11

  public:
    static ErrorMessages& getInstance();
    std::string getErrorMessage(Error);
};

class ImageLoaderException : public std::exception
{
  private:
    std::string m_functionName;
    unsigned int m_lineNumber;
    std::string m_message;

  public:
    ImageLoaderException(const std::string&, unsigned int, Error);
    ImageLoaderException(const std::string&, unsigned int, Error, const std::string&);
    const char* what() const noexcept;
};

#endif /* end of include guard: GNUCACHE_BILL_IMPORTER_H_EUZYAZPN */
