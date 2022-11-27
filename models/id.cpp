#include "id.hpp"

std::string param_to_id(const std::string& param)
{
  std::string result = param;

  for (int i = 0 ; i < result.length() ; ++i)
  {
    if (result[i] == '-')
      result[i] = ':';
  }
  return result;
}

