#pragma once
#include <comet/custom_element.hpp>
#include "models/field.hpp"

class ParameterView;

class FieldListItem : public Comet::CustomElement
{
public:
  virtual ~FieldListItem() {}

  void set_uri(const std::string& value)
  {
    uri = value;
    trigger_binding_updates();
  }

  void set_model(const std::shared_ptr<FieldModel>& value)
  {
    model = value;
    trigger_binding_updates();
  }

  void trigger_binding_updates() override;
  void clear();

private:
  std::shared_ptr<FieldModel> model;
  std::shared_ptr<ParameterView> type_el;
  std::string uri;
};
