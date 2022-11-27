#pragma once
#include "project.hpp"
#include <iostream>

class TypeSolver
{
public:
  void solve(const std::string& value)
  {
    auto project = ProjectModel::instance;
    auto finder = std::bind(&TypeSolver::matches_typename, this, std::placeholders::_1);

    type_name = simplified_name = value;
    if (value.find("<") != std::string::npos)
      simplified_name = value.substr(0, value.find("<"));
    ns_type = project.get_classes().find(finder);
    if (ns_type) return ;
    ns_type = project.get_namespaces().find(finder);
    if (ns_type) return ;
    ns_type = project.get_enums().find(finder);
    if (ns_type) return ;
    if (solve_external_type(simplified_name)) return ;
  }

  bool solve_external_type(const std::string& value)
  {
    DataTree& external_types = ProjectModel::instance.get_external_types();
    Data scope_data = external_types.as_data();
    std::string scope = value;
    std::size_t pos;

    if (scope[0] == ':' && scope[1] == ':')
      scope = scope.substr(2);
    while ((pos = scope.find("::")) != std::string::npos)
    {
      std::string scope_name = scope.substr(0, pos);

      scope = scope.substr(pos + 2);
      scope_data = scope_data[scope_name];
      if (!scope_data.exists())
        return false;
    }
    scope_data = scope_data[scope];
    external_type = scope_data.defaults_to<std::string>("");
    return external_type.length() > 0;
  }

  bool is_handled_type() const
  {
    return is_known_type() || is_external_type();
  }

  bool is_known_type() const
  {
    return ns_type != nullptr;
  }

  bool is_external_type() const
  {
    return external_type.length() > 0;
  }

  std::string get_style() const
  {
    if (is_known_type())
      return "outline-primary";
    else if (is_external_type())
      return "outline-dark";
    return "outline-secondary disabled";
  }

  std::string get_name() const
  {
    if (ns_type)
      return ns_type->get_name();
    else if (type_name.find("::") == 0)
      return type_name.substr(2);
    return type_name;
  }

  std::string get_link() const
  {
    if (ns_type)
      return ns_type->get_uri();
    if (external_type.length() > 0)
      return external_type;
    return "";
  }

  std::string get_link_target() const
  {
    if (ns_type)
      return "_self";
    return "_blank";
  }

  std::string get_title() const
  {
    if (ns_type)
      return ns_type->get_title();
    return type_name;
  }

  std::string get_excerpt_html() const
  {
    if (ns_type)
      return ns_type->get_excerpt();
    return "";
  }

private:
  bool matches_typename(const std::shared_ptr<NamespaceModel>& ns) const
  {
    return ns->get_full_name() == simplified_name;
  }

  std::string type_name;
  std::string simplified_name;
  std::shared_ptr<NamespaceModel> ns_type;
  std::string external_type;
};
