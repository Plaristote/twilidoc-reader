#pragma once
#include "templates/components/parameter.hpp"
#include "models/type_solver.hpp"

class ParameterView : public HtmlTemplate::Parameter
{
public:
  void set_model(const std::shared_ptr<ParamModel>& value) override
  {
    HtmlTemplate::Parameter::set_model(value);
    type_solver.solve(model->get_type_name());
    trigger_binding_updates();
  }

  std::string get_suffix() const override
  {
    std::string result;

    if (model)
    {
      for (int i = 0 ; i < model->ptr_count() ; ++i)
        result += '*';
      for (int i = 0 ; i < model->ref_count() ; ++i)
        result += '&';
    }
    return result;
  }
};
