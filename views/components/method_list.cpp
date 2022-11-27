#include "method_list.hpp"
#include <iostream>

using namespace std;

MethodListView::MethodListView() : Comet::CustomElement()
{
  add_class("method-list");
}

void MethodListView::set_methods(const MethodList& value)
{
  methods = value;
  trigger_binding_updates();
}

void MethodListView::set_fields(const FieldList& value)
{
  fields = value;
  trigger_binding_updates();
}

void MethodListView::set_visibility(CppVisibility value)
{
  visibility = value;
  trigger_binding_updates();
}

void MethodListView::reset()
{
  empty();
  method_els.clear();
}

void MethodListView::trigger_binding_updates()
{
  Comet::CustomElement::trigger_binding_updates();
  reset();
  for (const auto& method : methods)
  {
    if (should_display(method->get_visibility(), visibility))
      render_method(method);
  }
  for (const auto& field : fields)
  {
    if (should_display(field->get_visibility(), visibility))
      render_field(field);
  }
}

void MethodListView::render_method(const std::shared_ptr<MethodModel>& model)
{
  auto item = make_shared<MethodListItem>();

  method_els.push_back(item);
  item->set_model(model);
  *this > std::vector<Comet::Element>{
    Comet::Element("div", {{"class", "separator"}}),
    Comet::Element("span")
  };
  if (model->get_doc().length() && model->get_uri().length())
    item->set_uri(model->get_uri());
  item->each([this](Comet::Element& el)
  {
    *this > el;
    return true;
  });
  *this > Comet::Element("span");
}

void MethodListView::render_field(const std::shared_ptr<FieldModel>& model)
{
  auto item = make_shared<FieldListItem>();

  field_els.push_back(item);
  item->set_model(model);
  *this > std::vector<Comet::Element>{
    Comet::Element("div", {{"class", "separator"}}),
    Comet::Element("span")
  };
  if (model->get_doc().length() && model->get_uri().length())
    item->set_uri(model->get_uri());
  item->each([this](Comet::Element& el)
  {
    *this > el;
    return true;
  });
  *this > Comet::Element("span");
}
