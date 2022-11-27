#pragma once
#include <string>

enum CppVisibility
{
  PublicVisibility = 2,
  ProtectedVisibility = 1,
  PrivateVisibility = 0
};

CppVisibility string2visibility(const std::string& value);

const std::string& visibility2string(CppVisibility value);

bool should_display(CppVisibility source, CppVisibility required);
