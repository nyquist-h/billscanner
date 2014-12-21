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

class ImageLoaderException : public std::exception 
{
 private:
   std::string m_fileName;
   unsigned int m_lineNumber;
   std::string m_message;

 public:
   ImageLoaderException(std::string, unsigned int, std::string);
   const char* what() const noexcept;
};

#endif /* end of include guard: GNUCACHE_BILL_IMPORTER_H_EUZYAZPN */
