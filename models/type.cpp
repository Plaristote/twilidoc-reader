#include "type.hpp"
#include <iostream>

using namespace std;

void TypeModel::from_json(Data json_data)
{
  kind = static_cast<TypeKind>(json_data["kind"].defaults_to<int>(static_cast<int>(OtherKind)));
  raw_name = json_data["raw_name"].as<string>();
  name = json_data["name"].as<string>();
  full_name = json_data["full_name"].as<string>();
  scopes = json_data["scopes"].to_vector<string>();
  _is_const = json_data["const"].defaults_to<bool>(false);
  _ref_count = json_data["ref"].defaults_to<int>(0);
  _ptr_count = json_data["ptr"].defaults_to<int>(0);
  set_id(full_name + '#' + name);
}
