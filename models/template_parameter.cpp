#include "template_parameter.hpp"

TemplateParameter::TemplateParameter(Data json_data)
{
  type = json_data["type"].as<std::string>();
  name = json_data["name"].as<std::string>();
  default_value = json_data["default"].defaults_to<std::string>("");
}

void load_template_parameters(Data data, TemplateParameters& list)
{
  if (data.exists())
  {
    data.each([&list](Data param_data) -> bool
    {
      list.push_back(TemplateParameter(param_data));
      return true;
    });
  }
}
