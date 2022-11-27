#pragma once
#include <string>

struct PackageHelper
{
  static std::string uri(const std::string& base_uri, const std::string& package)
  {
    if (base_uri[0] == '#' && current_package.length() && package.length())
      return "#/packages/" + package + base_uri.substr(1);
    return base_uri;
  }

  static std::string current_package;
};
