#pragma once
#include "namespace.hpp"
#include <unordered_map>

class EnumModel : public NamespaceModel
{
public:
  std::string get_resource_name() const override { return "enums"; }
  const std::vector<std::pair<std::string, long long>>& get_values() const { return values; }

  void from_json(Data json_data) override
  {
    NamespaceModel::from_json(json_data);
    json_data["values"].each([this](Data value)
    {
      values.push_back({value["key"].as<std::string>(), value["value"].as<long long>()});
      return true;
    });
  }

  std::string get_title() const override { return "enum " + get_name(); }
private:
  std::vector<std::pair<std::string, long long>> values;
};
