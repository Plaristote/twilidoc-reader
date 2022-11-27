#include "field.hpp"
#include "class.hpp"

using namespace std;

void FieldModel::from_json(Data json_data)
{
  ParamModel::from_json(json_data);
  _is_static = json_data["static"].defaults_to(false);
  visibility = string2visibility(json_data["visibility"].defaults_to<string>(""));
  doc = json_data["doc"].defaults_to<string>("");
}

void FieldModel::load_list(Data list_data, std::vector<std::shared_ptr<FieldModel>>& list, ClassModel* parent)
{
  if (list_data.exists())
  {
    list_data.each([&list, parent](Data method_data) -> bool
    {
      auto model = make_shared<FieldModel>(parent);
      model->from_json(method_data);
      list.push_back(model);
      return true;
    });
  }
}

string FieldModel::get_uri() const
{
  if (parent)
    return "#/classes/" + parent->get_full_name() + '/' + get_name();
  return "";
}
