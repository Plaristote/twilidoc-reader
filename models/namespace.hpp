#pragma once
#include "application.hpp"
#include <set>

class NamespaceModel : public ApplicationModel
{
public:
  virtual std::string get_resource_name() const override { return "namespaces"; }
  std::string get_url() const override { return ""; }

  const std::string& get_name() const { return name; }
  const std::string& get_full_name() const { return full_name; }
  const std::string& get_package() const override { return package; }
  const std::string& get_excerpt() const { return excerpt; }
  const std::string& get_doc() const { return doc; }
  virtual std::string get_title() const { return "namespace " + name; }
  const std::set<std::string>& get_packages() const { return packages; }
  bool has_package(const std::string& value) const;
  void add_package(const std::string& value) { packages.insert(value); }
  bool are_packages_loaded() const { return package_initialized; }
  void set_packages_loaded() { package_initialized = true; }

  virtual void from_json(Data json_data) override;

  std::string to_json() const override { return ""; }

protected:
  std::string package;
  std::string name;
  std::string full_name;
  std::string excerpt;
  std::string doc;
  std::set<std::string> packages;
  bool package_initialized = false;
};
