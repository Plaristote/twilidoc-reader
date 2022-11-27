#pragma once
#include <comet/mvc/json_model.hpp>

class ParamModel : public Comet::JsonModel<>
{
public:
  const std::string& get_name() const { return name; }
  const std::string& get_type_name() const { return type_name; }
  const std::string& get_type_alias() const { return type_alias.length() ? type_alias : type_name ; }
  bool is_const() const { return _is_const; }
  int  ref_count() const { return _is_reference; }
  int  ptr_count() const { return _is_pointer; }

  bool operator==(const ParamModel& other) const
  {
    return type_name == other.type_name && is_const() == other.is_const() && ref_count() == other.ref_count() && ptr_count() == other.ptr_count();
  }

  void from_json(Data json_data) override
  {
    _is_const = json_data["const"].as<bool>();
    _is_reference = json_data["ref"].as<int>();
    _is_pointer = json_data["ptr"].as<int>();
    type_name = json_data["type"].as<std::string>();
    type_alias = json_data["alias"].defaults_to<std::string>("");
    name = json_data["name"].defaults_to<std::string>("");
  }

  std::string to_json() const override { return ""; }
  std::string get_url() const override { return ""; }

private:
  std::string type_name;
  std::string type_alias;
  std::string name;
  bool _is_const = false;
  int  _is_reference = 0;
  int  _is_pointer = 0;
};

typedef std::vector<std::shared_ptr<ParamModel>> ParamModels;
