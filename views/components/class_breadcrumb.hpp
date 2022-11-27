#pragma once
#include <comet/custom_element.hpp>
#include <map>

class NamespaceModel;
class FunctionModel;

class ClassBreadcrumb : public Comet::CustomElement
{
public:
  ClassBreadcrumb();
  void set_namespace(const NamespaceModel& ns);
  void set_function(const FunctionModel& ns);
  void trigger_binding_updates() override;

private:
  void generate_crumbs();
  std::map<std::string, std::string> fragments() const;

  std::string name;
  std::string full_name;
};
