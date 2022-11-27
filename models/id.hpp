#pragma once
#include <string>

template<typename MODEL>
std::string id_to_uri(const MODEL& model)
{
  std::string result = model.get_id();

  for (int i = 0 ; i < result.length() ; ++i)
  {
    if (result[i] == ':')
      result[i] = '-';
  }
  return result;
}

std::string param_to_id(const std::string& param);
