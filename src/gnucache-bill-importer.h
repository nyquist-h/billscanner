#ifndef GNUCACHE_BILL_IMPORTER_H_EUZYAZPN
#define GNUCACHE_BILL_IMPORTER_H_EUZYAZPN

#if defined(_MSC_VER)
  #define EXPORT __declspec(dllexport)
  #define IMPORT __declspec(dllimport)
#elif defined(__GNUG__)
  #define EXPORT
  #define IMPORT
#elif defined(__llvm__)
  #define EXPORT
  #define IMPORT
#else
  #error Unknown dynamic link import/export semantics.
#endif

#define PRINT(variable) #variable

#endif /* end of include guard: GNUCACHE_BILL_IMPORTER_H_EUZYAZPN */
