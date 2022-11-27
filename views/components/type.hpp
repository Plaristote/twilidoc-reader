#pragma once
#include "templates/components/type.hpp"

class TypeView : public HtmlTemplate::Type
{
public:
  void set_type_name(const std::string& value) override
  {
    HtmlTemplate::Type::set_type_name(value);
    type_solver.solve(value);
    trigger_binding_updates();
  }

private:
  bool has_popup() const override
  {
    return type_name != type_solver.get_title() || type_solver.get_excerpt_html().length();
  }

  std::string get_type_class() const override
  {
    std::string base;

    if (button)
    {
      base = "btn btn-sm btn-";
      base += has_link() ? type_solver.get_style().c_str() : "outline-secondary disabled";
    }
    if (type_solver.is_known_type())
      return base + " local-type";
    else if (type_solver.is_external_type())
      return base + " import-type";
    return base + " other-type";
  }
};
