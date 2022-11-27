#include "class.hpp"
#include <algorithm>

using namespace std;

shared_ptr<MethodModel> ClassModel::find_method(const string& name)
{
  auto it = find_if(methods.begin(), methods.end(), [name](const std::shared_ptr<MethodModel>& method)
  {
    return method->get_name() == name;
  });
  return it != methods.end() ? *it : nullptr;
}

void ClassModel::from_json(Data json_data)
{
  NamespaceModel::from_json(json_data);
  declared_as = json_data["type"].defaults_to<string>("class");
  include_path = json_data["include"].defaults_to<string>("");
  ldflags = json_data["link"].defaults_to<string>("");
  cmake_cmds = json_data["cmake"].defaults_to<string>("");
  if (json_data["inherits"].exists())
    bases = json_data["inherits"].to_vector<string>();
  MethodModel::load_list(json_data["constructors"], constructors, this);
  MethodModel::load_list(json_data["methods"], methods, this);
  FieldModel::load_list(json_data["fields"], fields, this);
  load_template_parameters(json_data["template_params"], template_parameters);
}

bool ClassModel::implements_virtual(const MethodModel& method) const
{
  for (const auto& candidate : methods)
  {
    if (candidate->implements(method))
      return true;
  }
  return false;
}

string ClassModel::get_title() const
{
  string result;

  if (is_template())
    result += "template ";
  result += get_declared_as() + ' ';
  result += get_name();
  return result;
}

set<string> ClassModel::get_documented_method_names() const
{
  set<string> list;

  for (const auto& method : methods)
  {
    if (method->get_doc().length())
      list.insert(method->get_name());
  }
  return list;
}

vector<shared_ptr<MethodModel>> ClassModel::get_methods_by_name(const string& name) const
{
  vector<shared_ptr<MethodModel>> list;

  copy_if(methods.begin(), methods.end(), back_inserter(list),
    [name](const shared_ptr<MethodModel>& model) { return model->get_name() == name; });
  return list;
}
