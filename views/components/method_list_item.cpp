#include "method_list_item.hpp"
#include "parameter.hpp"
#include "views/components/template_params.hpp"

using namespace std;

void MethodListItem::clear()
{
  empty();
  parameter_els.clear();
}

void MethodListItem::trigger_binding_updates()
{
  Comet::Element visibility_el ("div", {{"class", "visibility"}});
  Comet::Element return_type_el("div", {{"class", "return-type"}});
  Comet::Element name_el       ("div", {{"class", "method-name"}});
  Comet::Element all_params_el ("div", {{"class", "method-params"}});
  Comet::Element anotations_el ("div", {{"class", "method-anotations"}});
  Comet::Element tpl_params_el ("div", {{"class", "template-param-list"}});
  Comet::Element params_el     ("div", {{"class", "param-list"}});

  clear();
  visibility_el.add_class(visibility2string(model->get_visibility()));

  if (model->has_return_type())
  {
    auto param_view = make_shared<ParameterView>();

    param_view->set_model(model->get_return_type());
    param_view->bind_attributes();
    param_view->trigger_binding_updates();
    return_type_el > *param_view;
    parameter_els.push_back(param_view);
  }
  else if (!model->is_constructor())
    return_type_el.text("void").add_class("void-return-type");

  if (uri.length())
    name_el = Comet::Element("a", {{"class","method-name"},{"href",uri}});
  name_el.text(model->get_name());

  if (model->get_template_parameters().size())
  {
    auto param_view = make_shared<TemplateParamsView>();

    param_view->set_list(model->get_template_parameters());
    param_view->bind_attributes();
    param_view->trigger_binding_updates();
    all_params_el > *param_view;
    tpl_parameter_el = param_view;
  }

  for (const auto& param : model->get_params())
  {
    auto param_view = make_shared<ParameterView>();

    param_view->set_model(param);
    param_view->bind_attributes(),
    param_view->trigger_binding_updates();
    params_el > *param_view;
    parameter_els.push_back(param_view);
  }
  all_params_el > params_el;

  if (model->get_flags() & StaticMethod)
    anotations_el > Comet::Element("span", {{"class", "badge bg-primary"}}).text("static");
  if (model->get_flags() & ConstMethod)
    anotations_el > Comet::Element("span", {{"class", "badge bg-secondary"}}).text("const");
  if (model->get_flags() & PureVirtualMethod)
    anotations_el > Comet::Element("span", {{"class", "badge bg-danger"}}).text("pure virtual");
  else if (model->get_flags() & VirtualMethod)
    anotations_el > Comet::Element("span", {{"class", "badge bg-info"}}).text("virtual");

  *this > std::vector<Comet::Element>{
    visibility_el,
    return_type_el,
    name_el,
    all_params_el,
    anotations_el
  };
}
