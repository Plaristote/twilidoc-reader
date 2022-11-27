#pragma once
#include <comet/custom_element.hpp>
#include "method_list_item.hpp"
#include "field_list_item.hpp"

class MethodListView : public Comet::CustomElement
{
public:
  MethodListView();
  void set_methods(const MethodList& value);
  void set_fields(const FieldList& value);
  void set_visibility(CppVisibility value);
  void trigger_binding_updates() override;
  void reset();

private:
  void render_method(const std::shared_ptr<MethodModel>& method);
  void render_field(const std::shared_ptr<FieldModel>& field);

  MethodList methods;
  FieldList fields;
  CppVisibility visibility = PublicVisibility;
  std::list<std::shared_ptr<MethodListItem>> method_els;
  std::list<std::shared_ptr<FieldListItem>> field_els;
};
