#pragma once
#include <comet/mvc/json_model.hpp>
#include <set>
#include "collections/types.hpp"
#include "collections/functions.hpp"
#include "collections/namespaces.hpp"
#include "collections/classes.hpp"
#include "collections/enums.hpp"
#include <iostream>

class ProjectModel : public Comet::JsonModel<>
{
public:
  static ProjectModel instance;

  std::string get_url() const override { return "twili.json"; }

  void from_json(Data) override;

  std::string to_json() const override { return ""; }

  TypeCollection& get_types() { return types; }
  NamespaceCollection& get_namespaces() { return namespaces; }
  ClassCollection& get_classes() { return classes; }
  FunctionCollection& get_functions() { return functions; }
  DataTree& get_external_types() { return external_types; }
  EnumCollection& get_enums() { return enums; }
  const std::string& get_name() const { return name; }
  const std::string& get_logo() const { return logo; }
  const std::set<std::string>& get_packages() const { return packages; }
  std::string get_package_excerpt(const std::string& package) const;

  Comet::Object get_search_options();

  template<typename COLLECTION, typename CONTEXT>
  typename COLLECTION::Subset from_context(COLLECTION& collection, const std::shared_ptr<CONTEXT>& context, const std::string& package = "")
  {
    return collection.subset().where([context, package](const typename COLLECTION::Model& model) -> bool
    {
      if ((!package.length() || model.has_package(package)) &&
          (model.get_full_name().find(context->get_full_name() + "::") == 0))
      {
        const auto suffix = model.get_full_name().substr(context->get_full_name().length() + 2);
        return !typename_has_context(suffix);
      }
      return false;
    });
  }

  template<typename COLLECTION>
  typename COLLECTION::Subset from_root_context(COLLECTION& collection, const std::string& package = "")
  {
    return collection.subset().where([package](const typename COLLECTION::Model& model)
    {
      if (!package.length() || model.has_package(package))
      {
        const auto& name = model.get_full_name();
        const auto suffix = name.find("::") == 0 ? name.substr(2) : name;

        return !typename_has_context(suffix);
      }
      return false;
    });
  }

  Comet::Promise fetch();
  Comet::Promise fetch_external_types();

  MethodList collect_inherited_methods(const std::shared_ptr<ClassModel>& model, std::vector<std::shared_ptr<ClassModel>> parents)
  {
    MethodList result;

    parents.push_back(model);
    for (const std::string& base_name : model->get_bases())
    {
      std::shared_ptr<ClassModel> ancestor = classes.get(base_name);

      if (ancestor)
      {
        const auto& methods = ancestor->get_methods();
        auto        inherited_methods = collect_inherited_methods(ancestor, parents);

        std::copy_if(methods.begin(), methods.end(), std::back_inserter(result), [&parents](const std::shared_ptr<MethodModel>& method)
        {
          return !method->is_virtual() && !is_implemented_in_parents(method, parents);
        });
        std::copy(inherited_methods.begin(), inherited_methods.end(), std::back_inserter(result));
      }
    }
    return result;
  }

  static bool is_implemented_in_parents(const std::shared_ptr<MethodModel>& method, const std::vector<std::shared_ptr<ClassModel>>& parents)
  {
    for (const auto& parent : parents)
    {
      if (parent->implements_virtual(*method))
        return true;
    }
    return false;
  }

private:
  void probe_namespace_packages(const std::shared_ptr<NamespaceModel>&);

  static bool typename_has_context(const std::string& name)
  {
    for (int i = 0 ; i < name.length() ; ++i)
    {
      switch (name[i])
      {
        case ':':
          return true;
        case '<':
          return false;
      }
    }
    return false;
  }

  std::string         name, logo;
  TypeCollection      types;
  NamespaceCollection namespaces;
  ClassCollection     classes;
  FunctionCollection  functions;
  EnumCollection      enums;
  DataTree            external_types;
  std::set<std::string> packages;
  std::map<std::string, std::string> package_excerpts;
};
