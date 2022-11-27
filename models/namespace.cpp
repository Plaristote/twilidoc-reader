#include "namespace.hpp"
#include <algorithm>

using namespace std;

void NamespaceModel::from_json(Data json_data)
{
  if (json_data["module"].exists())
  {
    package = json_data["module"].as<string>();
    packages.insert(package);
  }
  name = json_data["name"].as<string>();
  full_name = json_data["full_name"].as<string>();
  doc = json_data["doc"].defaults_to<string>("");
  excerpt = json_data["excerpt"].defaults_to<string>("");
  set_id(full_name);
}

bool NamespaceModel::has_package(const string& value) const
{
  return find(packages.begin(), packages.end(), value) != packages.end();
}
