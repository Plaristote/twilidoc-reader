#pragma once
#include <comet/custom_element.hpp>
#include "models/method.hpp"

class ParameterView;
class TemplateParamsView;

class MethodListItem : public Comet::CustomElement
{
public:
  virtual ~MethodListItem() {}

  void set_uri(const std::string& value)
  {
    uri = value;
    trigger_binding_updates();
  }

  void set_model(const std::shared_ptr<InvokableModel>& value)
  {
    model = value;
    trigger_binding_updates();
  }

  void trigger_binding_updates() override;
  void clear();

private:
  std::shared_ptr<InvokableModel> model;
  std::list<std::shared_ptr<ParameterView>> parameter_els;
  std::shared_ptr<TemplateParamsView> tpl_parameter_el;
  std::string uri;
};
