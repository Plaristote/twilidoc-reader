#pragma once
#include "templates/components/visibility_picker.hpp"

class VisibilityPicker : public HtmlTemplate::VisibilityPicker
{
  static CppVisibility default_visibility;
public:
  VisibilityPicker();

  void pick_visibility(CppVisibility) override;
  std::string button_class(CppVisibility) const override;
};
