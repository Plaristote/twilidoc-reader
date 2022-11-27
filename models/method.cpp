#include "method.hpp"
#include "class.hpp"
#include <comet/globals.hpp>

using namespace std;

void MethodModel::from_json(Data json_data)
{
  int virtual_flag = json_data["virtual"].defaults_to<int>(0);

  InvokableModel::from_json(json_data);
  if (json_data["static"].defaults_to<bool>(false))
    flags = flags | StaticMethod;
  if (json_data["const"].defaults_to<bool>(false))
    flags = flags | ConstMethod;
  if (virtual_flag)
  {
    flags = flags | VirtualMethod;
    if (virtual_flag > 1)
      flags = flags | PureVirtualMethod;
  }
  visibility = string2visibility(json_data["visibility"].defaults_to<string>(""));
  set_id(name);
}

string MethodModel::get_uri() const
{
  if (parent)
  {
    string encoded_name = Comet::window.apply("encodeURI", Comet::String(get_name().c_str()));

    return "#/classes/" + parent->get_full_name() + '/' + encoded_name;
  }
  return "";
}

const string& MethodModel::get_package() const
{
  return parent->get_package();
}

bool MethodModel::is_constructor() const
{
  return parent && parent->get_name() == get_name();
}

void MethodModel::load_list(Data list_data, std::vector<std::shared_ptr<MethodModel>>& list, ClassModel* parent)
{
  if (list_data.exists())
  {
    list_data.each([&list, parent](Data method_data) -> bool
    {
      auto model = make_shared<MethodModel>(parent);
      model->from_json(method_data);
      list.push_back(model);
      return true;
    });
  }
}

bool MethodModel::implements(const MethodModel& other) const
{
  if (get_name() == other.get_name())
  {
    auto other_params = other.get_params();
    auto self_params = get_params();

    if (self_params.size() == other_params.size())
    {
      bool matches = true;

      for (int i = 0 ; i < self_params.size() ; ++i)
      {
        if (!(*self_params[i] == *other_params[i]))
        {
          matches = false;
          break ;
        }
      }
      if (matches)
        return true;
    }
  }
  return false;
}

bool has_pure_virtual_methods(const MethodList& list)
{
  for (const auto& method : list)
  {
    if (method->is_pure_virtual())
      return true;
  }
  return false;
}

