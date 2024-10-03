
#pragma once
#include <ceCore/coreexport.hh>
#include <exception>

namespace cryo
{

class FileNotOpenException : public std::exception
{
public:
  inline FileNotOpenException() : std::exception() { }
};

}