#include "gnucache-bill-importer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
using namespace std;

ImageLoaderException::ImageLoaderException(std::string fileName, unsigned int lineNumber,
    std::string message)
  : m_fileName(fileName), m_lineNumber(lineNumber), m_message(message) 
{ 
 //TODO logging
}

const char* ImageLoaderException::what() const noexcept
{
 return m_message.c_str(); 
}

int main()
{
  string str;
  cout << __FILE__<< endl;
  return 0;
}

