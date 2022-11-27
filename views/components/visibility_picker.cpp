#include "visibility_picker.hpp"

using namespace std;

CppVisibility VisibilityPicker::default_visibility = PublicVisibility;

VisibilityPicker::VisibilityPicker()
{
  value = default_visibility;
}

void VisibilityPicker::pick_visibility(CppVisibility v)
{
  value = default_visibility = v;
  trigger_binding_updates();
  signaler.trigger("visibility-change");
}

std::string VisibilityPicker::button_class(CppVisibility visibility) const
{
  string result = "btn btn-primary";

  if (visibility >= value)
    result += " active";
  return result;
}
