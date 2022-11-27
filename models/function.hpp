#pragma once
#include "invokable.hpp"

class FunctionModel : public InvokableModel
{
public:
  std::string get_resource_name() const override { return "functions"; }

  const std::string& get_name() const { return name; }
  const std::string& get_full_name() const { return full_name; }
  const std::string& get_include_path() const { return include_path; }
  const std::string& get_ldflags() const { return ldflags; }
  const std::string& get_cmake_cmds() const { return cmake_cmds; }
  const std::string& get_package() const override { return package; }
  bool has_package(const std::string& value) const { return package == value; }

  void from_json(Data json_data) override
  {
    InvokableModel::from_json(json_data);
    name = json_data["name"].as<std::string>();
    full_name = json_data["full_name"].as<std::string>();
    include_path = json_data["include"].as<std::string>();
    ldflags = json_data["link"].defaults_to<std::string>("");
    cmake_cmds = json_data["cmake"].defaults_to<std::string>("");
    package = json_data["module"].defaults_to<std::string>("");
    set_id(full_name);
  }

private:
  std::string name, full_name;
  std::string include_path;
  std::string ldflags;
  std::string cmake_cmds;
  std::string package;
};
