#include "visibility.hpp"
#include <map>

static const std::map<CppVisibility, std::string> visibility_names{
  {PublicVisibility, "public"},
  {ProtectedVisibility, "protected"},
  {PrivateVisibility, "private"}
};

CppVisibility string2visibility(const std::string& value)
{
  if (value == "protected") return ProtectedVisibility;
  return value == "private" ? PrivateVisibility : PublicVisibility;
}

const std::string& visibility2string(CppVisibility value)
{
  return visibility_names.at(value);
}

bool should_display(CppVisibility source, CppVisibility required)
{
  if (required == ProtectedVisibility)
    return source == PublicVisibility || source == ProtectedVisibility;
  return source == PublicVisibility || required == PrivateVisibility;
}
