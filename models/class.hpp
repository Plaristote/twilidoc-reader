#pragma once
#include <set>
#include "namespace.hpp"
#include "method.hpp"
#include "field.hpp"
#include "template_parameter.hpp"

class ClassModel : public NamespaceModel
{
public:
  std::string get_resource_name() const override { return "classes"; }

  std::string get_title() const override;
  const std::string& get_declared_as() const { return declared_as; }
  const std::string& get_include_path() const { return include_path; }
  const std::string& get_ldflags() const { return ldflags; }
  const std::string& get_cmake_cmds() const { return cmake_cmds; }
  const std::vector<std::string>& get_bases() const { return bases; }
  const MethodList& get_constructors() const { return constructors; }
  const MethodList& get_methods() const { return methods; }
  const FieldList& get_fields() const { return fields; }
  const TemplateParameters& get_template_parameters() const { return template_parameters; }
  bool is_template() const { return template_parameters.size() > 0; }
  std::shared_ptr<MethodModel> find_method(const std::string& name);
  bool implements_virtual(const MethodModel&) const;

  std::set<std::string> get_documented_method_names() const;
  std::vector<std::shared_ptr<MethodModel>> get_methods_by_name(const std::string&) const;

  void from_json(Data) override;

private:
  std::string include_path;
  std::string ldflags;
  std::string cmake_cmds;
  std::string declared_as;
  std::vector<std::string> bases;
  MethodList constructors;
  MethodList methods;
  FieldList  fields;
  TemplateParameters template_parameters;
};
