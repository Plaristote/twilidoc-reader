#include "field_list_item.hpp"
#include "views/components/parameter.hpp"
#include <iostream>

using namespace std;

void FieldListItem::clear()
{
  empty();
  type_el = nullptr;
}

void FieldListItem::trigger_binding_updates()
{
  Comet::Element visibility_el ("div", {{"class", "visibility"}});
  Comet::Element return_type_el("div", {{"class", "return-type"}});
  Comet::Element name_el       ("div", {{"class", "field-name"}});
  Comet::Element anotations_el ("div", {{"class", "field-anotations"}});
  shared_ptr<ParameterView> param_view;

  clear();
  visibility_el.add_class(visibility2string(model->get_visibility()));
  param_view = make_shared<ParameterView>();
  param_view->set_model(model);
  param_view->set_with_name(false);
  param_view->bind_attributes();
  param_view->trigger_binding_updates();
  return_type_el > *param_view;
  type_el = param_view;

  if (uri.length())
    name_el = Comet::Element("a", {{"class","method-name"},{"href",uri}});
  name_el.text(model->get_name());

  if (model->is_static())
    anotations_el > Comet::Element("span", {{"class", "badge bg-primary"}}).text("static");
  if (model->is_const())
    anotations_el > Comet::Element("span", {{"class", "badge bg-secondary"}}).text("const");

  *this > std::vector<Comet::Element>{
    visibility_el,
    return_type_el,
    name_el,
    anotations_el
  };
}
