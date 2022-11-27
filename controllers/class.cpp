#include "class.hpp"
#include "models/project.hpp"
#include "views/class.hpp"
#include <iostream>

using namespace std;

static shared_ptr<ClassView> current_view;
static shared_ptr<ClassModel> current_model;

ClassController::ClassController(const Comet::Params& params) : ApplicationController(params)
{
}

void ClassController::show()
{
  cout << "ClassController::show: " << params.at("id") << endl;
  if (!view_already_attached(params.at("id")))
  {
    const auto& model = find_class();
    auto view = render_class(model);

    if (view)
      fetch_method_documentations(view, model);
  }
}

void ClassController::method()
{
  const auto& model = find_class();
  string method_name = Comet::window.apply("decodeURI", Comet::String(params.at("path")));

  if (view_already_attached(params.at("id")))
  {
    current_view->scroll_to_method(method_name);
  }
  else
  {
    auto view = render_class(model);

    if (view)
    {
      fetch_method_documentations(view, model).then([view, method_name]()
      {
        view->scroll_to_method(method_name);
      });
    }
  }
}

shared_ptr<ClassModel> ClassController::find_class()
{
  const string id = params.at("id");
  const auto& model = ProjectModel::instance.get_classes().get(id);

  return model;
}

bool ClassController::view_already_attached(const string& id) const
{
  return current_view && current_model && current_view->is_attached() && current_model->get_id() == id;
}

shared_ptr<ClassView> ClassController::render_class(const std::shared_ptr<ClassModel>& model)
{
  if (model)
  {
    auto& project = ProjectModel::instance;
    auto view = make_shared<ClassView>();

    if (model->get_doc().length() > 0)
      fetch_documentation(model->get_doc(), bind(&ClassView::set_documentation, view, placeholders::_1));
    view->set_subclasses(project.from_context(project.get_classes(), model));
    view->set_enums(project.from_context(project.get_enums(), model));
    view->set_model(model);
    default_layout().render(view);
    current_view = view;
    current_model = model;
    return view;
  }
  else
    render_404(std::stringstream() << "class " << params.at("id") << " not found");
  return nullptr;
}

Comet::Promise ClassController::fetch_method_documentations(
  const shared_ptr<ClassView>& view,
  const shared_ptr<ClassModel>& model)
{
  vector<Comet::Promise> promises;

  for (const string& name : model->get_documented_method_names())
  {
    auto methods = model->get_methods_by_name(name);
    const auto& uri = (*methods.begin())->get_doc();

    promises.push_back(fetch_documentation(uri, [name, view](const string& doc)
    {
      view->set_method_documentation(name, doc);
    }));
  }
  return Comet::Promise::all(promises).then([view]()
  {
    view->trigger_binding_updates();
  });
}
