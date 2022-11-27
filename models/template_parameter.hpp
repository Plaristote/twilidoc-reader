#pragma once
#include <vector>
#include <string>
#include <comet/datatree.hpp>

struct TemplateParameter
{
  TemplateParameter() {}
  TemplateParameter(Data json_data);

  std::string type;
  std::string name;
  std::string default_value;
};

typedef std::vector<TemplateParameter> TemplateParameters;

void load_template_parameters(Data data, TemplateParameters& list);
