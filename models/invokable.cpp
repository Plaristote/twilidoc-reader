#include "invokable.hpp"

using namespace std;
  
void InvokableModel::from_json(Data json_data)
{
  name = json_data["name"].as<string>();
  doc = json_data["doc"].defaults_to<string>("");
  excerpt = json_data["excerpt"].defaults_to<string>("");
  if (json_data["returns"].exists())
  {
    return_type = make_shared<ParamModel>();
    return_type->from_json(json_data["returns"]);
  }
  if (json_data["params"].exists())
  {
    json_data["params"].each([this](Data param_data) -> bool
    {
      auto new_param = make_shared<ParamModel>();
      new_param->from_json(param_data);
      params.push_back(new_param);
      return true;
    });
  }
  load_template_parameters(json_data["template_params"], template_params);
}
