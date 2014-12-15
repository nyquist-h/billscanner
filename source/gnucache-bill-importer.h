#ifndef GNUCACHE_BILL_IMPORTER_H_EUZYAZPN
#define GNUCACHE_BILL_IMPORTER_H_EUZYAZPN

#if defined(_MSC_VER)
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(_GCC)
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#elif defined(__llvm__)
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    #error Unknown dynamic link import/export semantics.
#endif

#endif /* end of include guard: GNUCACHE_BILL_IMPORTER_H_EUZYAZPN */
